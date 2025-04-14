#include "classes.hpp"

#include "utils.hpp"

// Permission class implementation
Permission::Permission()
{
    _permissions.insert({'r', false});
    _permissions.insert({'w', false});
    _permissions.insert({'x', false});
}

void Permission::print_permission_options()
{
    for (auto& _permission : _permissions)
    {
        std::cout << std::to_string(_permission.first);
    }
}

std::string Permission::current_permissions()
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

void Permission::change_permission(char perm, bool value)
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

// Inode class implementation
Inode::Inode() : file_name(""), size(sizeof(file_name) + sizeof(size)), file_ext(""), permissions(Permission())
{
    available_exts[0] = ".jpg";
    available_exts[1] = ".txt";
    available_exts[2] = ".zip";
    available_exts[3] = ".exe";
    available_exts[4] = ".pdf";
    available_exts[5] = ".cpp";
    available_exts[6] = ".cs";
}

void Inode::set_metadata()
{
    print_divider("Set Inode data");
    file_name = get_string("Enter the file name: ");
    file_ext = get_ext();
    std::cout << "Operation was completed" << std::endl;
}

std::string Inode::get_ext()
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

void Inode::print_ext_options()
{
    print_divider("Extension Options");

    for (int i = 0; i < 7; i++)
    {
        std::cout << available_exts[i] << std::endl;
    }
}

// File class implementation
int File::master_counter = 0;

File::File() : ID(++master_counter), inode(Inode()), contents("") {}

// File_System class implementation
File_System::File_System() = default;

void File_System::add_file()
{
    std::lock_guard<std::mutex> lock(_mutex);
    File new_file;
    print_divider("Creation Manager");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flush buffer.
    new_file.inode.set_metadata();

    _files.insert({new_file.ID, new_file});
}

void File_System::remove_file()
{
    std::lock_guard<std::mutex> lock(_mutex);
    print_divider("Deletion Menu");

    int id = get_valid_ID();

    _files.erase(id);

    std::cout << "File [" + std::to_string(id) + "] has been successfully removed!" << std::endl;
}

void File_System::print_files_data()
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

    std::cout << "Total file/s -> " + std::to_string(_files.size()) << std::endl;
}

void File_System::append_text()
{
    print_divider("Append mode");
    std::lock_guard<std::mutex> lock(_mutex);
    int id = get_valid_ID();
    bool access = check_valid_permission('w', id);

    if (access)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer from new lines.
        std::string content = get_string("Enter the text you want to append: ");
        _files[id].contents += content;

        print_internal_divider();
        std::cout << "Your text was successfully added to the file with the ID of " + std::to_string(id) << std::endl;
    }
    else
    {
        std::cout << "You don't have the correct permission/s, you need [w] permission/s" << std::endl;
    }
}

void File_System::overwrite_text()
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
    else
    {
        std::cout << "You don't have the correct permission/s, you need [w] permission/s" << std::endl;
    }
}

void File_System::read_text()
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
    else
    {
        std::cout << "You don't have the correct permission/s, you need the [r] permission/s" << std::endl;
    }
}

void File_System::change_file_permission()
{
    print_divider("File Permission Modification");
    std::lock_guard<std::mutex> lock(_mutex);

    int id = get_valid_ID();
    char perm = get_char("Enter the permission you would like to modify (r/w/x): ");
    bool value = get_bool("Grant permission?: ");

    _files[id].inode.permissions.change_permission(perm, value);
}

void File_System::print_current_permission()
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

bool File_System::check_valid_permission(char perm, int id) { return _files[id].inode.permissions.current_permissions().find(perm) != std::string::npos; }

void File_System::encrypt_decrypt()
{
    print_divider("Encrypt/Decrypt Manager");
    std::lock_guard<std::mutex> lock(_mutex);

    int id = get_int("Enter the target file ID: ");
    std::string text = _files[id].contents;
    std::string encrypted_text = "";
    std::string key = create_encrypt_key();

    for (int i = 0; i < text.length(); i++)
    {
        char encrypted_char = text[i] ^ key[i % key.length()];
        encrypted_text += encrypted_char;
    }

    _files[id].contents = encrypted_text;
    loading_animation(5);
    std::cout << "Files have been encrypted successfully!" << std::endl;
}

// Move `get_valid_ID` from virtualFileManager.cpp
int File_System::get_valid_ID()
{
    int id = get_int("Enter a file ID: ");
    if (_files.find(id) == _files.end())
    {
        std::cout << "The ID was not found!" << std::endl;
        return get_valid_ID();
    }
    return id;
}

// Move `create_encrypt_key` from virtualFileManager.cpp
std::string File_System::create_encrypt_key()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    print_internal_divider();

    std::string key = get_string("Please enter your Key: ");

    std::cout << "The key [" << key << "] has been generated successfully." << std::endl;
    std::cout << "MAKE SURE TO WRITE THIS DOWN, IF THE KEY IS LOST, SO IS YOUR DATA" << std::endl;
    std::cout << "If the encrypt key is entered incorrectly, the data will be re-encrypted and therefore lost." << std::endl;

    pause_key();

    return key;
}