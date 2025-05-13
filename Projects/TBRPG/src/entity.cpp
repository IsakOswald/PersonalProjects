#include <iostream>
#include "entity.hpp"

namespace Entities
{

    Entity::Entity(std::string n, int h, int c, Weapon* w) : name(n), health(h), currency(c), weapon(w) {}
    Entity::~Entity() { delete weapon; }

    std::string Entity::getRole() const noexcept { return "Entity"; }

    void Entity::attack(Entity& enemy) noexcept
    {
        std::cout << getRole() << " is attacking " << enemy.name << '\n';

        enemy.health -= weapon->damage;

        if (enemy.health < 0)
        {
            enemy.health = 0;
        }

        std::cout << enemy.getRole() << " was hit for " << std::to_string(weapon->damage) << " damage" << '\n';
    }

    void Entity::battle(Entity& enemy) noexcept
    {
        while (health > 0 && enemy.health > 0)
        {
            attack(enemy);

            if (enemy.health == 0)
            {
                std::cout << getRole() << " killed the " << enemy.getRole() << '\n';
                std::cout << "You recieved " << enemy.currency << " currency" << '\n';
                currency += enemy.currency;
                return;
            }

            enemy.attack(*this);

            if (health == 0)
            {
                std::cout << enemy.getRole() << " killed the " << getRole();
                return;
            }
        }
    }
}  // namespace Entities
