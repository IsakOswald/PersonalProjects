#pragma once

#include <string>

struct Entity;

struct Weapon
{
    std::string name;
    int damage;
    int healing;

    Weapon(std::string n, int d, int h);
};
