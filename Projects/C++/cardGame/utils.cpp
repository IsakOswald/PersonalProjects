#include "utils.hpp"

#include <iostream>
#include <limits>

int getValidInteger(const std::string& prompt)
{
    int value;

    while (true)
    {
        std::cout << prompt;

        if (std::cin >> value)
        {
            return value;
        }
        else
        {
            std::cout << "Invalid input. Please enter a valid integer.\n";

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
