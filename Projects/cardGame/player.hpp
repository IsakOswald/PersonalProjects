#pragma once

#include "card.hpp"

namespace Core
{
    struct Player
    {
        std::string name;
        std::vector<Card> cards;
        int money;

        Player(std::string name);

        int getIndex() const noexcept;
    };
}  // namespace Core
