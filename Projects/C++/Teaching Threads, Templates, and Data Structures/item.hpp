#pragma once
#include <string>

// This is our Item sturct, it will hold some data about what entites are holding in their inventory.
struct Item
{
    // Each item should have a name (sword, potion, magic staff, etc)
    std::string name;
    // How much damage the Item will do (if its a weapon or some sort of damage potion)
    int damage;

    // How much healing the item will do (if its a healing potion, or may a magic staff that healts you as you attack)
    int healing;
    // The quatities of the items, for example, you could have 5 potions, or 30 arrows.
    int quantity;

    // Our constructor for Item.
    Item(std::string n, int d, int h, int q);
};
