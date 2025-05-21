#pragma once
#include <string>

struct Action
{
    std::string name;
    int currencyPerIter;
    int healthPerIter;
    int iterations;

    Action(std::string n, int cpi, int hpi, int i);
};
