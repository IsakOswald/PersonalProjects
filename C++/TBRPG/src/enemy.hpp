#pragma once
#include "entity.hpp"

namespace Entities
{

    struct Enemy : public Entity
    {
        Enemy(std::string n, int h, int c, Weapon* w);

        std::string getRole() const noexcept override;
    };
}  // namespace Entities
