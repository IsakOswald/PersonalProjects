#pragma once

#include "utils.h"

void print_main_menu()
{
    print_divider("Main Menu");
    std::cout << "[1] Create a file" << std::endl;
    std::cout << "[2] Print files data" << std::endl;
    std::cout << "[3] Append text to file" << std::endl;
    std::cout << "[4] Read file" << std::endl;
    std::cout << "[5] Print change file permissions" << std::endl;
    std::cout << "[6] Print view permissions" << std::endl;
    std::cout << "[0] Quit" << std::endl;
}

void file_menu() {}
void text_menu() {}
void permissions_menu() {}