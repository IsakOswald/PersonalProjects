#pragma once
#include "includes.h"

std::string get_string(const std::string& prompt)
{
    std::string user_input;

    std::cout << prompt;
    std::getline(std::cin, user_input);

    return user_input;
}

int get_int(const std::string& prompt)
{
    int user_input;

    std::cout << prompt;

    while (true)
    {
        if (std::cin >> user_input)
        {
            return user_input;
        }
        else
        {
            std::cout << "Please enter a valid integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double get_double(const std::string& prompt)
{
    double user_input;

    std::cout << prompt;

    while (true)
    {
        if (std::cin >> user_input)
        {
            return user_input;
        }
        else
        {
            std::cout << "Please enter a valid floating-point number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void print_divider(std::string title)
{  // Applying color and bold to the title
    std::cout << "\033[1;34m=====================> \033[1;32m" << title << " \033[1;34m<=====================\n";
}

void print_internal_divider() { std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << '\n'; }