#pragma once

#include <string>

namespace Core
{
    struct Weapon
    {
        std::string name;
        int damage;
        int healing;

        Weapon(std::string name, int damage, int healing);
    };

}  // namespace Core
