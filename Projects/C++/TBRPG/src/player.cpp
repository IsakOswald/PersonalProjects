#include <iostream>
#include <thread>
#include <chrono>
#include "player.hpp"
#include "entity.hpp"

namespace Entities
{

    Player::Player(std::string n, int h, int c, Weapon* w) : Entity(n, h, c, w) { actions = {Action("Meditation", 0, 5, 1), Action("Pick Pocket", 4, 0, 5)}; }

    std::string Player::getRole() const noexcept { return "Player"; }

    void Player::printActions() noexcept
    {
        std::cout << getRole() << " Actions Available: " << '\n';

        for (Action& action : actions)
        {
            std::cout << action.name << '\n';
        }
    }

    void Player::autoAction(Action& action) noexcept
    {
        std::cout << action.name << '\n';

        for (int i = 0; i < action.iterations; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            std::lock_guard<std::mutex> lock(playerMtx);
            currency += action.currencyPerIter;
            health += action.healthPerIter;
        }

        std::cout << "Action finished!" << '\n';
    }

}  // namespace Entities
