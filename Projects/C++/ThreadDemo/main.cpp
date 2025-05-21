#include "entity.hpp"
#include "shop.hpp"
#include <thread>
#include <iostream>

int main(int argc, char** argv)
{
    Entity* entities[] = {new Entity("Slime", 15.0f, 1.0f)};

    Entity player("Saky", 100.0f, 0.0f);

    Shop shop1;

    std::thread goldT(&Entity::autoFarm, std::ref(player), 5, 2.5);
    std::thread fightT(&Entity::fight, &player, std::ref(player), std::ref(*entities[0]), 3);

    fightT.join();
    goldT.join();

    player.printWeaponStats();

    shop1.printShop();

    std::cout << player.health << '\n';

    delete entities[0];

    return 0;
}
