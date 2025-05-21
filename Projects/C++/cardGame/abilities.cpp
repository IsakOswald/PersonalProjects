

#include "abilities.hpp"

using namespace Core;

Ability::Ability(std::string name, int damageBuff, int healingBuff, int ManaCost) : name(name), damageBuff(damageBuff), healingBuff(healingBuff), ManaCost(ManaCost) {}
