#include "run_menu.hpp"

#include "classes.hpp"
#include "includes.hpp"
#include "menu_templates.hpp"
#include "utils.hpp"

void run_main_menu(File_System& fs)
{
    int choice;

    // Keep asking to user to perform actions
    do
    {
        // Clear the screen to avoid pages of terminal output.
        clear_screen();
        print_main_menu();

        choice = get_int("Enter a choice: ");

        // Based on the main menu options, perform the corrsponding actions.
        switch (choice)
        {
            case 1:
                run_file_menu(fs);
                break;
            case 2:
                run_text_menu(fs);
                break;
            case 3:
                run_permissions_menu(fs);
                break;
            case 4:
                run_encrypt_decrypt_menu(fs);
                break;
            case 5:
                run_save_load_menu(fs);
                break;
            case 0:
                std::cout << "Quitting!" << std::endl;
                break;
            default:
                std::cout << "Not a valid option!" << std::endl;
                break;
        }
    } while (choice != 0);  // Loop unless the user wants to quit.
}

//! +++++++++++++++
//! All of the other file menus are similar, however perform different actions.
//! +++++++++++++++

void run_file_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_file_menu();

        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.add_file();
                pause_timer();
                break;
            case 2:
                fs.remove_file();
                pause_timer();
                break;
            case 3:
                fs.print_files_data();
                pause_key();
                break;
            case 0:
                std::cout << "Returning to the main menu" << std::endl;
                break;
            default:
                std::cout << "Not a valid option!" << std::endl;
                break;
        }
    } while (choice != 0);
}
void run_permissions_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_permissions_menu();

        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.print_current_permission();
                pause_key();
                break;
            case 2:
                fs.change_file_permission();
                pause_timer();
                break;
            case 0:
                std::cout << "Returning to the main menu" << std::endl;
                break;
            default:
                std::cout << "Not a valid option" << std::endl;
                break;
        }
    } while (choice != 0);
}
void run_text_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_text_menu();

        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.append_text();
                pause_timer();
                break;
            case 2:
                fs.overwrite_text();
                pause_timer();
                break;
            case 3:
                fs.read_text();
                pause_key();
                break;
            case 0:
                std::cout << "Returning to the main menu" << std::endl;
                break;
            default:
                std::cout << "Not a valid option" << std::endl;
                break;
        }
    } while (choice != 0);
}

void run_encrypt_decrypt_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_encrypt_decrypt_menu();

        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.encrypt_decrypt();
                pause_timer();
                break;

            case 0:
                std::cout << "Returning to the main menu" << std::endl;
                break;
            default:
                std::cout << "Not a valid option" << std::endl;
                break;
        }
    } while (choice != 0);
}

void run_save_load_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_save_load_menu();

        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.save_to_disk();
                loading_animation(3);
                break;
            case 2:
                fs.read_from_disk();
                loading_animation(3);
                break;

            case 0:
                std::cout << "Returning to the main menu" << std::endl;
                break;
            default:
                std::cout << "Not a valid option" << std::endl;
                break;
        }
    } while (choice != 0);
}
