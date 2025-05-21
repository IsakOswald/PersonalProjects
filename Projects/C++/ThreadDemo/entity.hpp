#pragma once
#include <string>
#include <mutex>
#include "weapon.hpp"

struct Entity
{
    std::string name;
    float health;
    float gold;
    Weapon weapon;
    std::mutex mtx;

    Entity(std::string n, float h, float g);

    void addGold(float ammount);
    void decreaseGold(float ammount);

    void autoFarm(int iterations, float increase);

    void printWeaponStats();

    void damage(Entity& entity, float damage);

    void fight(Entity& entity1, Entity& entity2, int fights);
};
