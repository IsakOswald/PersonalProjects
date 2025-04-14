#include "includes.hpp"
#include "menu_templates.hpp"
#include "run_menu.hpp"
#include "utils.hpp"

int main()
{
    File_System my_file_system;

    std::thread thread1(run_main_menu, std::ref(my_file_system));

    thread1.join();

    return 1;
}
