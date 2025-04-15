#include "includes.hpp"
#include "menu_templates.hpp"
#include "run_menu.hpp"
#include "utils.hpp"

// Global variable to control thread.
bool keep_running = true;

//! This is for a thread to auto save files.
void auto_save(File_System& fs)
{
    int elapsed_seconds = 0;
    const int SAVE_INTERVAL = 120;

    while (keep_running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        elapsed_seconds++;

        if (elapsed_seconds >= SAVE_INTERVAL)
        {
            fs.save_to_disk();
            std::cout << "\n[AutoSave] File system saved to disk.\n";
            elapsed_seconds = 0;
        }
    }

    // Final save before exiting the thread
    fs.save_to_disk();
    std::cout << "\n[AutoSave] Final save before exit.\n";
}

int main()
{
    // Look for debuggers attached.
    anti_debug_ptrace();
    // New File_System obj.
    File_System my_file_system;

    print_splash_screen();

    //! The auto saving thread.
    std::thread auto_saver(auto_save, std::ref(my_file_system));

    run_main_menu(my_file_system);

    //! After the thread is told to stop, load for 10 seconds to make sure it has saved.
    keep_running = false;
    std::cout << "[Please Wait] Integrity of files being verified." << std::endl;
    auto_saver.join();  // Wait for autosave thread to finish.
    loading_animation(3);
    std::cout << "Done. Thank you" << std::endl;

    return 0;
}
