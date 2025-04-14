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
            std::cout << "The permission " << std::to_string(_permissions[perm]) << " was updated";
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

        if (!found)
        {
            std::cout << "The ID was not found!" << std::endl;
            return get_valid_ID();
        }

        return -1;
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

        std::cout << "The file with the ID " << std::to_string(id) << " permissions have be updated!" << std::endl;
    }

    void print_current_permission()
    {
        print_divider("Current Permissions");

        std::lock_guard<std::mutex> lock(_mutex);

        int id = get_valid_ID();

        std::cout << "Current Permissions ->" << _files[id].inode.permissions.current_permissions() << std::endl;
    }

    bool check_valid_permission(char perm, int id)
    {
        if (_files[id].inode.permissions.current_permissions().find(perm) != std::string::npos)
        {
            return true;
        }

        return false;
    }
};

//? Function declarations
void run_fs(File_System& fs);
void print_main_menu();

int main()
{
    File_System my_file_system;

    std::thread thread1(run_fs, std::ref(my_file_system));

    thread1.join();

    return 1;
}

void run_fs(File_System& fs)
{
    int choice;

    do
    {
        print_main_menu();
        choice = get_int("Enter a choice: ");

        switch (choice)
        {
            case 1:
                fs.add_file();
                break;
            case 2:
                fs.print_files_data();
                break;
            case 3:
                fs.append_text();
                break;
            case 4:
                fs.read_text();
                break;
            case 5:
                fs.change_file_permission();
                break;
            case 6:
                fs.print_current_permission();
                break;
        }

    } while (choice != 0);
}

void file_thread(File_System& fs) {}

void text_thread(File_System& fs) {}

void permissions_thread(File_System& fs) {}

void encryption_thread(File_System& fs) {}

void saving_thread(File_System& fs) {}
