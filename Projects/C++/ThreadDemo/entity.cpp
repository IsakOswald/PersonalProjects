#include "entity.hpp"
#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>

Entity::Entity(std::string n, float h, float g) : name(n), health(h), gold(g), weapon("Fists", 3.0f, 0.0f, 0.0f) {}

void Entity::addGold(float ammount) { gold += ammount; }
void Entity::decreaseGold(float ammount) { gold -= ammount; }

void Entity::autoFarm(int iterations, float increase)
{
    std::cout << "Initial Gold: " << std::to_string(gold) << '\n';
    for (int i = 0; i < iterations; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::lock_guard<std::mutex> lock(mtx);

        addGold(increase);

        std::cout << gold << '\n';
    }

    std::cout << "You now have " << std::to_string(gold) << " gold." << '\n';
}

void Entity::printWeaponStats()
{
    std::cout << "Weapon: " << weapon.name << '\n';
    std::cout << "Damage: " << std::to_string(weapon.damage) << '\n';
    std::cout << "Healing: " << std::to_string(weapon.healing) << '\n';
}

void Entity::damage(Entity& entity, float damage)
{
    entity.health -= damage;
    if (entity.health < 0)
    {
        entity.health = 0;
    }
}

void Entity::fight(Entity& entity1, Entity& entity2, int fights)
{
    float initialEntity2 = entity2.health;

    for (int i = 0; i < fights; i++)
    {
        entity2.health = initialEntity2;

        std::cout << "Battle has begun!" << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(4));

        while (entity1.health > 0 && entity2.health > 0)
        {
            damage(entity2, entity1.weapon.damage);
            damage(entity1, entity2.weapon.damage);
        }

        if (entity1.health > 0)
        {
            std::cout << "The Player Wins!" << '\n';
            std::cout << "Gold gained: " << entity2.gold << '\n';

            std::lock_guard<std::mutex> lock(mtx);
            addGold(entity2.gold);
        }
        else
        {
            std::cout << "You Died!" << '\n';
            return;
        }
    }
}
