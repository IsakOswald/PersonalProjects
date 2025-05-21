#pragma once

#include "weapon.hpp"

namespace Entities
{

    struct Entity
    {
        std::string name;
        int health;
        int currency;
        Weapon* weapon;

        Entity(std::string n, int h, int c, Weapon* w);
        ~Entity();

        virtual std::string getRole() const noexcept;

        void attack(Entity& enemy) noexcept;
        void battle(Entity& enemy) noexcept;
    };
}  // namespace Entities
