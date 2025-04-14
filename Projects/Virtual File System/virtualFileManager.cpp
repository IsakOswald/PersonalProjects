#include "includes.h"
#include "menus.h"
#include "threads.h"
#include "utils.h"

class Permission
{
   private:
    std::unordered_map<char, bool> _permissions;

   public:
    Permission()
    {
        _permissions.insert({'r', false});
        _permissions.insert({'w', false});
        _permissions.insert({'x', false});
    }

    void print_permission_options()
    {
        for (auto& _permission : _permissions)
        {
            std::cout << std::to_string(_permission.first);
        }
    }

    std::string current_permissions()
    {
        std::string result;

        for (auto& _permission : _permissions)
        {
            if (_permission.second)
            {
                result += _permission.first;
            }

            else
            {
                result += "-";
            }
        }

        return result;
    }

    void change_permission(char perm, bool value)
    {
        if (_permissions.find(perm) != _permissions.end())
        {
            _permissions[perm] = value;
            std::cout << "The permission " << std::to_string(_permissions[perm]) << " was updated" << std::endl;
        }

        else
        {
            std::cout << "Not a valid permission!" << std::endl;
        }
    }
};

class Inode
{
   public:
    std::string file_name;
    size_t size;
    std::string file_ext;
    std::string available_exts[7];
    Permission permissions;

    Inode() : file_name(""), size(sizeof(file_name) + sizeof(size)), file_ext(""), permissions(Permission())
    {
        available_exts[0] = ".jpg";
        available_exts[1] = ".txt";
        available_exts[2] = ".zip";
        available_exts[3] = ".exe";
        available_exts[4] = ".pdf";
        available_exts[5] = ".cpp";
        available_exts[6] = ".cs";
        // Add others at your own will.

    }  // Constructor.

    void set_metadata()
    {
        print_divider("Set Inode data");
        file_name = get_string("Enter the file name: ");
        file_ext = get_ext();
        std::cout << "Operation was completed" << std::endl;
    }

   private:
    std::string get_ext()
    {
        std::string input = get_string("Enter the desired file type: ");
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (const std::string& ext : available_exts)
        {
            if (ext == input)
            {
                return ext;
            }
        }

        std::cout << "Not a valid file type!" << std::endl;
        print_ext_options();

        return get_ext();
    }

    void print_ext_options()
    {
        print_divider("Extension Options");

        for (int i = 0; i < 7; i++)
        {
            std::cout << available_exts[i] << std::endl;
        }
    }
};

class File
{
   private:
    static int master_counter;

   public:
    int ID;
    Inode inode;
    std::string contents;

    File() : ID(++master_counter), inode(Inode()), contents("") {}  // Constructor. Create the ID number based off the static master counter.
};

int File::master_counter = 0;

class File_System
{
   private:
    std::unordered_map<int, File> _files;
    std::mutex _mutex;

    int get_valid_ID()
    {
        int id = get_int("Enter a file ID: ");
        bool found = false;

        for (auto& file : _files)
        {
            if (file.first == id)
            {
                found = true;

                std::cout << "ID is valid." << std::endl;
                return id;
            }
        }

        while (_files.size() == 0)
        {
            std::cout << "You do not currently have any files" << std::endl;
            return -1;
        }

        if (!found)
        {
            std::cout << "The ID was not found!" << std::endl;
            return get_valid_ID();
        }

        return -1;
    }

    std::string create_encrypt_key()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        print_internal_divider();

        std::string key = get_string("Please enter you Key: ");

        std::cout << "The key [" << key << "] has been generated successfully." << std::endl;

        std::cout << "MAKE SURE TO WRITE THIS DOWN, IF THE KEY IS LOST, SO IS YOU DATA" << std::endl;
        std::cout << "If encrypt key is entered incorrectly, the data will be re-encrypted and therefore lost." << std::endl;

        pause_key();

        return key;
    }

   public:
    File_System() = default;  // Use the default constructors for the hasmap and mutex.

    // A function that adds a new file to the hasmap.
    void add_file()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        File new_file;
        print_divider("Creation Manager");

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flush buffer.
        // Set the new files inode data.
        new_file.inode.set_metadata();

        _files.insert({new_file.ID, new_file});
    }

    void remove_file()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        print_divider("Deletion Menu");

        int id = get_valid_ID();

        _files.erase(id);

        std::cout << "File [" + std::to_string(id) + "] has been successfully removed!" << std::endl;
    }

    void print_files_data()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        print_divider("File Data");

        for (auto& file : _files)
        {
            std::cout << "File ID -> " << std::to_string(file.first) << std::endl;

            std::cout << "File Name -> " << file.second.inode.file_name << std::endl;

            std::cout << "Extension type -> " << file.second.inode.file_ext << std::endl;

            std::cout << "Size -> " << std::to_string(file.second.inode.size) + " bytes" << std::endl;

            std::cout << "Permissions -> " + file.second.inode.permissions.current_permissions() << std::endl;

            print_internal_divider();
        }

        std::cout << " Total file/s -> " + std::to_string(_files.size()) << std::endl;
    }

    void append_text()
    {
        print_divider("Append mode");
        std::lock_guard<std::mutex> lock(_mutex);
        int id = get_valid_ID();
        bool access = check_valid_permission('w', id);

        if (access)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer from new lines. Make sure that the get_string is read properly.

            std::string content = get_string("Enter the text you want to append: ");

            _files[id].contents += content;

            print_internal_divider();

            std::cout << "Your text was successfully added to the file with the ID of " + std::to_string(id) << std::endl;
        }

        if (!access)
        {
            std::cout << "You dont have the correct permission/s, you need [w] permission/s" << std::endl;
        }
    }

    void overwrite_text()
    {
        print_divider("Overwrite Mode");
        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_valid_ID();
        bool access = check_valid_permission('w', id);

        if (access)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string content = get_string("Enter the text you want to write: ");
            _files[id].contents = content;

            print_internal_divider();

            std::cout << "Your text was successfully added to the file with the ID of " + std::to_string(id) << std::endl;
        }

        if (!access)
        {
            std::cout << "You dont have the correct permission/s, you need [w] permission/s" << std::endl;
        }
    }

    void read_text()
    {
        print_divider("Read mode");
        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_valid_ID();
        bool access = check_valid_permission('r', id);

        if (access)
        {
            std::cout << "Attempting to read contents of file " + std::to_string(id) + "." << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            std::cout << "Contents : " << _files[id].contents + "[EOF]" << std::endl;
        }

        if (!access)
        {
            std::cout << "You dont have the correct permission/s, you need the [r] permission/s" << std::endl;
        }
    }

    void change_file_permission()
    {
        print_divider("File Permission Modification");

        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_valid_ID();

        char perm = get_char("Enter the permission you would like to modify (r/w/x): ");

        bool value = get_bool("Grand permission?: ");

        _files[id].inode.permissions.change_permission(perm, value);
    }

    void print_current_permission()
    {
        print_divider("Current Permissions");

        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_valid_ID();

        if (_files[id].inode.permissions.current_permissions() == "---")
        {
            std::cout << "You currently have no permissions!" << std::endl;
        }

        else
        {
            std::cout << "Current Permissions -> " << _files[id].inode.permissions.current_permissions() << std::endl;
        }
    }

    bool check_valid_permission(char perm, int id)
    {
        if (_files[id].inode.permissions.current_permissions().find(perm) != std::string::npos)
        {
            return true;
        }

        return false;
    }

    void encrypt_decrypt()
    {
        print_divider("Encrypt/Decrypt Manager");
        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_int("Enter the target file ID: ");

        // Get the contents of the file before we replace it.
        std::string text = _files[id].contents;
        // Create a variable to store the encrypted text.
        std::string encrypted_text = "";

        std::string key = create_encrypt_key();

        for (int i = 0; i < text.length(); i++)
        {
            // If we mod the i value, we restart the encryption key if the key is shorted then the string.
            char encrypted_char = text[i] ^ key[i % key.length()];
            encrypted_text += encrypted_char;
        }

        // Set the files contents to the new encrypted text.
        _files[id].contents = encrypted_text;

        loading_animation(5);

        std::cout << "Files have been encrypted successfully!" << std::endl;
    }
};

//? Function declarations
void run_main_menu(File_System& fs);
void run_file_menu(File_System& fs);
void run_permissions_menu(File_System& fs);
void run_text_menu(File_System& fs);
void run_encrypt_decrypt_menu(File_System& fs);

int main()
{
    File_System my_file_system;

    std::thread thread1(run_main_menu, std::ref(my_file_system));

    thread1.join();

    return 1;
}

void run_main_menu(File_System& fs)
{
    int choice;

    do
    {
        clear_screen();
        print_main_menu();

        choice = get_int("Enter a choice: ");

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
            case 0:
                std::cout << "Quitting!" << std::endl;
                break;
            default:
                std::cout << "Not a valid option!" << std::endl;
                break;
        }
    } while (choice != 0);
}

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