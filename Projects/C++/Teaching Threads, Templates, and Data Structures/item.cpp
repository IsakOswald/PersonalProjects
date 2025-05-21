#include <string>
#include "item.hpp"

// Only need a constructor the Item::Item part means <Struct>::<Function>.
// So this means that we are referring to the Item struct, inside of the item struct we are referring to
// the Item function (our constructor)
Item::Item(std::string n, int d, int h, int q) : name(n), damage(d), healing(h), quantity(q) {}
