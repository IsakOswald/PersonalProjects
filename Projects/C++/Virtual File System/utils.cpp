#include "includes.hpp"

//? A function to get a string based upon a prompt
std::string get_string(const std::string& prompt)
{
    std::string user_input;

    std::cout << prompt;
    std::getline(std::cin, user_input);

    return user_input;
}
//? A function to get a valid int based upon a prompt
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
//? A function to get a valid doubled based upon a prompt
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
//? A function to get a valid bool based upon a prompt
bool get_bool(const std::string& prompt)
{
    std::string user_input;

    std::cout << prompt << " (yes/no): ";
    while (true)
    {
        std::getline(std::cin, user_input);

        // Convert to lowercase for flexibility.
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
//? A function to get a valid char based upon a prompt
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer from new lines.
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return user_input;
        }
    }
}
//? A function to print a nice divider with coloured output.
void print_divider(std::string title)
{  // Applying color and bold to the title
    std::cout << "\033[1;34m=====================> \033[1;32m" << title << " \033[1;34m<=====================\n";
}
//? A smaller internal divider.
void print_internal_divider() { std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << '\n'; }

//! Clear the terminal output
void clear_screen() { system("clear"); }

//? A function to pause the users input for a period of time.
void pause_timer() { std::this_thread::sleep_for(std::chrono::milliseconds(1650)); }

//? Pause the input until user presses enter.
void pause_key()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nPress Enter to continue...";
    std::cin.get();  // Wait for Enter.
}

void loading_animation(int iters)
{
    std::string prompt = "Loading";
    std::string dots = "";

    for (int i = 0; i < iters; i++)
    {
        dots += ".";                                                  // Add one dot per iteration, this will give loading effect.
        std::cout << "\r" << prompt << dots << std::flush;            // Use carriage return to overwrite the same line.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Delay for the animation of loading.
    }

    std::cout << std::endl;  // After animation is complete move to the next line.
}

void anti_debug_ptrace()
{
    if (ptrace(PT_DENY_ATTACH, 0, 0, 0) != 0)
    {
        std::cout << "Debugger detected. Exiting...\n";
        exit(1);
    }
}
