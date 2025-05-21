#include <iostream>
#include "player.hpp"
#include "utils.hpp"

using namespace Core;

Player::Player(std::string name) : name(name), money(10) { cards.push_back(Card("Rat", cardType::ASSASSIN, std::make_unique<Weapon>("Serated Tooth", 5, 0), 12, 3, 5, 15, {Ability("Poision Tooth", 5, 0, 2)})); }

int Player::getIndex() const noexcept
{
    int userInput;

    for (int i = 0; i < cards.size(); i++)
    {
        std::cout << (i + 1) << "-> " << cards[i].cardName << '\n';
    }

    do
    {
        userInput = getValidInteger("Enter the desired card: ");

    } while (userInput < 1 || userInput > cards.size());

    return userInput - 1;
}
