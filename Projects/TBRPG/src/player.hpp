#pragma once

#include <mutex>
#include <vector>
#include "entity.hpp"
#include "action.hpp"

namespace Entities
{

    struct Player : public Entity
    {
        std::vector<Action> actions;
        std::mutex playerMtx;

        Player(std::string n, int h, int c, Weapon* w);

        std::string getRole() const noexcept override;

        void printActions() noexcept;
        void autoAction(Action& action) noexcept;
    };

}  // namespace Entities
