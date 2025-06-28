#include "weapon.hpp"

Weapon::Weapon() : name("Unknown"), damage(0.0f), healing(0.0f), cost(0.0f) {}
Weapon::Weapon(std::string n, float d, float h, float c) : name(n), damage(d), healing(h), cost(c) {}
