#pragma once

#include <string>

namespace Core
{
    struct Ability
    {
        std::string name;
        int damageBuff;
        int healingBuff;
        int ManaCost;

        Ability(std::string name, int damageBuff, int healingBuff, int ManaCost);
    };
}  // namespace Core
