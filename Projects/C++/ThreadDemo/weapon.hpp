#pragma once
#include <string>

struct Weapon
{
    std::string name;
    float damage;
    float healing;
    float cost;

    Weapon();
    Weapon(std::string n, float d, float h, float c);
};
