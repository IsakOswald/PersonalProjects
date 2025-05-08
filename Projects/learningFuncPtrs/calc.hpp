#pragma once

struct Calc
{
    void (Calc::*funcPtr)(int, int);

    Calc();

    void add(int var1, int var2);

    void execute(int var1, int var2);
};
