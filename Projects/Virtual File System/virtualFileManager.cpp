#include "utils.h"

class Inode
{
   public:
    std::string file_name;
    size_t size;
    std::string file_ext;
    std::string available_exts[7];

    Inode() : file_name(""), size(sizeof(file_name) + sizeof(size)), file_ext("")
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

    void add_content() { contents = get_string("Enter the file contents"); }
};

int File::master_counter = 0;

class File_System
{
   private:
    std::unordered_map<int, File> _files;
    std::mutex _mutex;

    int get_valid_ID()
    {
        int id = get_int("Enter a files ID to delete");
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

    // A function that adds a file to the
    void add_file()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        File new_file;
        print_divider("Creation Manager");

        // Set the new files inode data
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
            std::cout << "File ID -> " + std::to_string(file.first) << std::endl;

            std::cout << "File Name -> " + file.second.inode.file_name << std::endl;

            std::cout << "Extension type -> " + file.second.inode.file_ext << std::endl;

            std::cout << "Size -> " + std::to_string(file.second.inode.size) + " bytes" << std::endl;

            print_internal_divider();
        }

        std::cout << " Total file/s -> " + std::to_string(_files.size()) << std::endl;
    }
};

//? Function declarations
void run_fs(File_System& fs);

int main()
{
    File_System my_file_system;

    std::thread thread1(run_fs, std::ref(my_file_system));

    thread1.join();

    return 1;
}

void run_fs(File_System& fs)
{
    fs.add_file();
    fs.add_file();
    fs.print_files_data();
    fs.remove_file();
    fs.print_files_data();
}
