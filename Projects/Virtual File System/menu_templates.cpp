#include "utils.hpp"

// This is our menu for the main menu
void print_main_menu()
{
    print_divider("Main Menu");
    std::cout << "[1] FILE MENU" << std::endl;
    std::cout << "[2] TEXT MENU" << std::endl;
    std::cout << "[3] PERMISSIONS MENU" << std::endl;
    std::cout << "[4] ENCRYPTION MENU" << std::endl;
    std::cout << "[5] DISK MENU" << std::endl;
    std::cout << "[0] QUIT" << std::endl;
}
// Menu for the file related options
void print_file_menu()
{
    print_divider("File Menu");
    std::cout << "[1] Add File" << std::endl;
    std::cout << "[2] Remove File" << std::endl;
    std::cout << "[3] Print File Data" << std::endl;
    std::cout << "[0] Back to Main Menu" << std::endl;
}
// Menu for the related text options
void print_text_menu()
{
    print_divider("Text Menu");
    std::cout << "[1] Append Text" << std::endl;
    std::cout << "[2] Overwrite Text" << std::endl;
    std::cout << "[3] Read Text" << std::endl;
    std::cout << "[0] Back to Main Menu" << std::endl;
}
// Menu for the permission related options
void print_permissions_menu()
{
    print_divider("Permissions Menu");
    std::cout << "[1] Print File Permissions" << std::endl;
    std::cout << "[2] Modify File Permissions" << std::endl;
    std::cout << "[0] Back to Main Menu" << std::endl;
}
// Menu for the encrypt/decrypt options.
void print_encrypt_decrypt_menu()
{
    print_divider("Encryption/Decrypt menu");
    std::cout << "[1] Encrypt/Decrypt" << std::endl;
    std::cout << "[0] Back to Main Menu" << std::endl;
    std::cout << "Note: You can use option one to both encrypt and decrypt you files." << std::endl;
}
// The Persistence options
void print_save_load_menu()
{
    print_divider("Persistence Manager");
    std::cout << "[1] Save current files" << std::endl;
    std::cout << "[2] Load existing files" << std::endl;
    std::cout << "[0] Back to Main Menu" << std::endl;
}

void print_splash_screen()
{
    std::cout << R"(
        __     __     ______     __         ______     __  __    
       /\ \  _ \ \   /\  ___\   /\ \       /\  __ \   /\ \_\ \   
       \ \ \/ ".\ \  \ \ \____  \ \ \____  \ \ \/\ \  \ \____ \  
        \ \__/".~\_\  \ \_____\  \ \_____\  \ \_____\  \/\_____\ 
         \/_/   \/_/   \/_____/   \/_____/   \/_____/   \/_____/ 
                                                                 
                V I R T U A L   F I L E   M A N A G E R          
       )" << std::endl;

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}