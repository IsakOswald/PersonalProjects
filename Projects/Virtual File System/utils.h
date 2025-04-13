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

bool get_bool(const std::string& prompt)
{
    std::string user_input;

    std::cout << prompt << " (yes/no): ";
    while (true)
    {
        std::getline(std::cin, user_input);

        // Convert to lowercase for consistency
        std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);

        if (user_input == "yes" || user_input == "y" || user_input == "true" || user_input == "1")
        {
            return true;
        }
        else if (user_input == "no" || user_input == "n" || user_input == "false" || user_input == "0")
        {
            return false;
        }
        else
        {
            std::cout << "Please enter 'yes' or 'no': ";
        }
    }
}

char get_char(const std::string& prompt)
{
    char user_input;

    std::cout << prompt;

    while (true)
    {
        std::cin >> user_input;

        if (std::cin.fail())
        {
            std::cout << "Please enter a valid character: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear rest of line
            return user_input;
        }
    }
}

void print_divider(std::string title)
{  // Applying color and bold to the title
    std::cout << "\033[1;34m=====================> \033[1;32m" << title << " \033[1;34m<=====================\n";
}

void print_internal_divider() { std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << '\n'; }