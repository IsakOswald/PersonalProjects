#pragma once
#include <string>
#include "weapon.hpp"

constexpr int MAX_CAPACITY = 3;

struct Shop
{
    std::string merchant;
    Weapon inventory[MAX_CAPACITY];

    Shop();

    void printShop();
};
