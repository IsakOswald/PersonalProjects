#include <iostream>
#include "calc.hpp"

Calc::Calc() : funcPtr(&Calc::add) {}

void Calc::add(int var1, int var2) { std::cout << var1 + var2 << '\n'; }

void Calc::execute(int var1, int var2) { (this->*funcPtr)(var1, var2); }
