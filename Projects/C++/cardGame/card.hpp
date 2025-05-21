#pragma once

#include <string>
#include <vector>
#include "cardType.hpp"
#include "abilities.hpp"
#include "weapon.hpp"

constexpr int MANA_REGEN = 2;

namespace Core
{
    struct Card
    {
        std::string cardName;
        cardType type;
        std::unique_ptr<Weapon> weapon;
        int health;
        int defense;
        int maxMana;

        int sellValue;

        std::vector<Ability> abilities;

        Card(std::string n, cardType t, std::unique_ptr<Weapon> w, int h, int d, int mM, int sV, std::vector<Ability> a);

        void printStats();
        void printCardAbilities();

        void attack(Card& enemy);
        void battle(Card& enemy);
    };

}  // namespace Core
