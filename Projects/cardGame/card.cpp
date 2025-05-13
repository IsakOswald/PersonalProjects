#include <iostream>
#include "card.hpp"

using namespace Core;

Card::Card(std::string n, cardType t, std::unique_ptr<Weapon> w, int h, int d, int mM, int sV, std::vector<Ability> a) : cardName(n), type(t), weapon(std::move(w)), health(h), defense(d), maxMana(mM), sellValue(sV), abilities(std::move(a)) {}

void Card::printCardAbilities()
{
    for (Ability& ability : abilities)
    {
        std::cout << ability.name << '\n';
    }
}

void Card::printStats()
{
    std::cout << "---- CARD STAT MENU ----" << '\n' << '\n';

    std::cout << "Name -> " << cardName << '\n';
    std::cout << "Type -> " << '\n';
    std::cout << "Weapon -> " << weapon->name << '\n';
    std::cout << "Health -> " << health << '\n';
    std::cout << "Defense -> " << defense << '\n';
    std::cout << "Max Mana -> " << maxMana << '\n';
    std::cout << "Sell Value -> " << sellValue << '\n';
    std::cout << "Abilities -> " << '\n';
    printCardAbilities();

    std::cout << '\n';
}

void Card::attack(Card& enemy)
{
    std::cout << cardName << " is attacking " << enemy.cardName << " with " << weapon->name << '\n';
    enemy.health -= weapon->damage;

    std::cout << enemy.cardName << " was attacked for " << weapon->damage << " damage" << '\n';

    if (enemy.health < 0)
    {
        enemy.health = 0;
    }
}

void Card::battle(Card& enemy)
{
    std::cout << "The battle has started between " << cardName << " and " << enemy.cardName << '\n';

    while (health > 0 && enemy.health > 0)
    {
        attack(enemy);
        if (enemy.health == 0)
        {
            std::cout << enemy.cardName << " has been defeated.\n";
            return;
        }

        enemy.attack(*this);

        if (health == 0)
        {
            std::cout << "Since you have died, the card will be removed from your inventory. Be more careful!\n";
            return;
        }
    }
}
