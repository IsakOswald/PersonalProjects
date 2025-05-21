#include <iostream>
#include "shop.hpp"
#include "weapon.hpp"

Shop::Shop() : merchant("Wandering Trader")
{
    inventory[0] = Weapon("Club", 5.0f, 0.0f, 20.0f);
    inventory[1] = Weapon("Sword", 15.0f, 0.0f, 50.0f);
    inventory[2] = Weapon(" Magical Staff", 3.0f, 4.0f, 35.0f);
}

void Shop::printShop()
{
    for (int i = 0; i < MAX_CAPACITY; i++)
    {
        std::cout << inventory[i].name << '\n';
        std::cout << "Damage :" << inventory[i].damage << '\n';
        std::cout << "Healing : " << inventory[i].healing << '\n';
        std::cout << "Price : " << inventory[i].cost << '\n';

        std::cout << '\n';
    }

    std::cout << '\n';
}
