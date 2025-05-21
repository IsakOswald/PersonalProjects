#include "enemy.hpp"

namespace Entities
{

    Enemy::Enemy(std::string n, int h, int c, Weapon* w) : Entity(n, h, c, w) {}

    std::string Enemy::getRole() const noexcept { return "Enemy"; }
}  // namespace Entities
