#include <vector>

#include "entity.hpp"
#include "player.hpp"
#include "enemy.hpp"

void freeMem(std::vector<Entity*> entities) noexcept;

int main()
{
    Entities::Player p1("Isak", 100, 5, new Weapon("Club", 15, 0));

    std::vector<Entities::Entity*> enemies = {new Entities::Enemy("Rat", 15, 5, new Weapon("Poision Tooth", 4, 0))};

    p1.battle(*enemies[0]);
}

void freeMem(std::vector<Entities::Entity*> entities) noexcept
{
    for (Entities::Entity* e : entities)
    {
        delete e;
    }
}
