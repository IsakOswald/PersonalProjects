#include "classes.hpp"

#include "utils.hpp"

// Default constructor
Permission::Permission()
{
    // Add the bits that we want each file to have. I chose read (r), write(w), and execute (x) bits
    _permissions.insert({'r', false});
    _permissions.insert({'w', false});
    _permissions.insert({'x', false});
}
// Printing the permission options the user has.
void Permission::print_permission_options()
{
    // For every key value pair in _permissions:
    for (auto& _permission : _permissions)
    {
        // Print the ID (which is the key in our hasmap)
        std::cout << std::to_string(_permission.first);
    }
}
// Check the files current permissions
std::string Permission::current_permissions()
{
    // Create a string used for outputting the permissions.
    std::string result;

    // Loop through the has map (<char permission, bool has_permission>)
    for (auto& _permission : _permissions)
    {
        // Check if the has_permission is set.
        if (_permission.second)
        {
            result += _permission.first;
        }
        // If it is not, just print a dash.
        else
        {
            result += "-";
        }
    }

    // Return the result in the form of 'rwx' or '---';
    return result;
}
// Chang the files current permissions.
void Permission::change_permission(char perm, bool value)
{
    // Check if the permission the user wants to change exists in the map (rwx).
    if (_permissions.find(perm) != _permissions.end())  // .end() is kind of like a nullptr
    {
        // Change the permission to the value the user entered.
        _permissions[perm] = value;
        std::cout << "The permission " << std::to_string(_permissions[perm]) << " was updated" << std::endl;
    }
    // If the permission entered is not r,w, or x display that its not valid.
    else
    {
        std::cout << "Not a valid permission!" << std::endl;
    }
}
// load the permissions from the file (this is used for persistence)
void Permission::load_from_string(const std::string& perm_string)
{
    // Make sure that the perm length is r,w, or x (length 3).
    if (perm_string.length() != 3)
    {
        std::cerr << "Invalid permission string length.\n";
        return;
    }

    const std::string keys = "rwx";
    // Loop through the permissions and set them to the key value pair.
    for (size_t i = 0; i < 3; ++i)
    {
        char key = keys[i];
        char val = perm_string[i];

        // If the value is equal to the key set the permission to true.
        if (val == key)
        {
            _permissions[key] = true;
        }
        // Other wise set it to nothing (-)
        else if (val == '-')
        {
            _permissions[key] = false;
        }
        // If these either are not met it means it was an invalid permission.
        else
        {
            std::cerr << "Invalid permission character: " << val << '\n';
        }
    }
}
// Constructor
Inode::Inode() : file_name(""), size(sizeof(file_name) + sizeof(size)), file_ext(""), permissions(Permission())
{
    // Set the file extensions that the user can pick from for their files.
    available_exts[0] = ".jpg";
    available_exts[1] = ".txt";
    available_exts[2] = ".zip";
    available_exts[3] = ".exe";
    available_exts[4] = ".pdf";
    available_exts[5] = ".cpp";
    available_exts[6] = ".cs";
    // More can easily be added here if you want. For example you could add .lua support
}
// Set the metadata for the file like size, name, file type, etc.
void Inode::set_metadata()
{
    // Get the files name and the desired file type.
    print_divider("Set Inode data");
    file_name = get_string("Enter the file name: ");
    file_ext = get_ext();
    std::cout << "Operation was completed" << std::endl;
}
// Get the extension the user wants
std::string Inode::get_ext()
{
    std::string input = get_string("Enter the desired file type: ");
    // Transform the string to lowercase. .end() and .begin() are iterators.
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    // Loop through the available extension option
    for (const std::string& ext : available_exts)
    {
        // Compare the user input to the available files extensions
        if (ext == input)
        {
            // Return the extension if the user selects and available option
            return ext;
        }
    }

    // If the user does not select a valid permission:
    std::cout << "Not a valid file type!" << std::endl;
    // Print the available methods they have to pick from.
    print_ext_options();

    // Recursively call the function until they select a valid option.
    return get_ext();
}

// Print the available extension options
void Inode::print_ext_options()
{
    print_divider("Extension Options");

    // Loop through the available extension options.
    for (int i = 0; i < 7; i++)
    {
        // Print each option to the terminal
        std::cout << available_exts[i] << std::endl;
    }
}

// This is the files static master counter.
// Make sure that the files do not have a overlapping ID (like a file systems process table).
int File::master_counter = 0;
// Constructor
File::File() : ID(++master_counter), inode(Inode()), contents("") {}

// Constructor for file system.
File_System::File_System() = default;

// A function to add a file to the hasmap
void File_System::add_file()
{
    //! Used for thread safety avoiding things like race conditions.
    // Lock the function from other threads.
    std::lock_guard<std::mutex> lock(_mutex);
    // Create a new file obj.
    File new_file;
    print_divider("Creation Manager");

    // Flush the buffer of new lines.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Set the meta data for the new file
    new_file.inode.set_metadata();

    // .insert is how we add a new key:vale pair to a hashmap.
    _files.insert({new_file.ID, new_file});
}
// Allow the user to remove files (deleting them)
void File_System::remove_file()
{
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);
    print_divider("Deletion Menu");

    // Get a valid id
    int id = get_valid_ID();

    // .erase removes the key value pair from the hasmap.
    _files.erase(id);

    // Let the user know what file they removed.
    std::cout << "File [" + std::to_string(id) + "] has been successfully removed!" << std::endl;
}
// Print some data about the files currently on the system.
void File_System::print_files_data()
{
    // Lock the tread.
    std::lock_guard<std::mutex> lock(_mutex);
    print_divider("File Data");

    // For every <ID : File> in our files hasmap
    for (auto& file : _files)
    {
        // Print some stats about the files.
        std::cout << "File ID -> " << std::to_string(file.first) << std::endl;
        std::cout << "File Name -> " << file.second.inode.file_name << std::endl;
        std::cout << "Extension type -> " << file.second.inode.file_ext << std::endl;
        std::cout << "Size -> " << std::to_string(file.second.inode.size) + " bytes" << std::endl;
        std::cout << "Permissions -> " + file.second.inode.permissions.current_permissions() << std::endl;
        print_internal_divider();
    }

    // Also let the user know how many files they have in their system
    std::cout << "Total file/s -> " + std::to_string(_files.size()) << std::endl;
}
// Add text to a file.
void File_System::append_text()
{
    print_divider("Append mode");
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);
    // Get a valid ID
    int id = get_valid_ID();
    //! Check if the file has the correct permission set
    bool access = check_valid_permission('w', id);

    // If the do have access:
    if (access)
    {
        // Flush the buffer of new lines.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Get the content the user wants to append to the file.
        std::string content = get_string("Enter the text you want to append: ");
        // Append the user input to the files contents.
        _files[id].contents += content;  // Since we are using += contents, we are appending not overwriting.

        print_internal_divider();
        std::cout << "Your text was successfully added to the file with the ID of " + std::to_string(id) << std::endl;
    }
    // If the user does not have the correct permission bit let them know.
    else
    {
        std::cout << "You don't have the correct permission/s, you need [w] permission/s" << std::endl;
    }
}

// Over write the text of a file.
void File_System::overwrite_text()
{
    print_divider("Overwrite Mode");
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get a valid ID and check if the file has right permissions.
    int id = get_valid_ID();
    bool access = check_valid_permission('w', id);

    // If they have the right permission:
    if (access)
    {
        // Flush the buffer.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Get the content they want to write and over-write and over-write it into the file.
        std::string content = get_string("Enter the text you want to write: ");
        _files[id].contents = content;  // '=' means overwrite.

        print_internal_divider();
        std::cout << "Your text was successfully added to the file with the ID of " + std::to_string(id) << std::endl;
    }
    // If the user does not have permission.
    else
    {
        std::cout << "You don't have the correct permission/s, you need [w] permission/s" << std::endl;
    }
}

// Read the contents of a file
void File_System::read_text()
{
    print_divider("Read mode");
    // Block other threads.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get file ID and check file has 'r' permission.
    int id = get_valid_ID();
    bool access = check_valid_permission('r', id);

    // If the user has access
    if (access)
    {
        // Read the contents of the file.
        std::cout << "Attempting to read contents of file " + std::to_string(id) + "." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Sleep the current thread 200ms.
        // Print the contents of the file.
        std::cout << "Contents : " << _files[id].contents + "[EOF]" << std::endl;
    }
    // If the user does not have permissions.
    else
    {
        std::cout << "You don't have the correct permission/s, you need the [r] permission/s" << std::endl;
    }
}
// Modify the files permissions
void File_System::change_file_permission()
{
    print_divider("File Permission Modification");
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get id, permission to modify, and true/false depending if they want to give or take the permission.
    int id = get_valid_ID();
    char perm = get_char("Enter the permission you would like to modify (r/w/x): ");
    bool value = get_bool("Grant permission?: ");

    // Reflect the changes in the real file.
    _files[id].inode.permissions.change_permission(perm, value);
}
// Check the current files permissions
void File_System::print_current_permission()
{
    print_divider("Current Permissions");
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get id.
    int id = get_valid_ID();

    // Check if the file has no permissions at all.
    if (_files[id].inode.permissions.current_permissions() == "---")
    {
        // Print no permissions.
        std::cout << "You currently have no permissions!" << std::endl;
    }
    // If the user does have atleast one permission set:
    else
    {
        // Output the permission.
        std::cout << "Current Permissions -> " << _files[id].inode.permissions.current_permissions() << std::endl;
    }
}
// Check valid permission. Check the entered permission is either 'r', 'w', or 'x'.
bool File_System::check_valid_permission(char perm, int id) { return _files[id].inode.permissions.current_permissions().find(perm) != std::string::npos; }

//! Allow user to encrypt and decrypt their file contnets.
void File_System::encrypt_decrypt()
{
    print_divider("Encrypt/Decrypt Manager");
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get id and string text.
    int id = get_int("Enter the target file ID: ");
    std::string text = _files[id].contents;
    std::string encrypted_text = "";
    // Get the user to create an encrypt key.
    std::string key = create_encrypt_key();

    // Loop through each char in the conents of the file.
    for (int i = 0; i < text.length(); i++)
    {
        // XOR the text char (i) and the key char (i).
        char encrypted_char = text[i] ^ key[i % key.length()];  // Make sure to mod this so we dont get out of bounds issues.
        // Add the XOR'd char into the encrypted text.
        encrypted_text += encrypted_char;
    }

    // Set the files contents to the new encrypted text.
    _files[id].contents = encrypted_text;
    // Loading animation.
    loading_animation(5);
    std::cout << "Files have been encrypted successfully!" << std::endl;
}
// Make sure the user is requesting a valid file ID.
int File_System::get_valid_ID()
{
    int id = get_int("Enter a file ID: ");
    // If the user id is not found:
    if (_files.find(id) == _files.end())
    {
        std::cout << "The ID was not found!" << std::endl;
        return get_valid_ID();
    }

    // Otherwise we can just return the valid id.

    return id;
}
// Allow the user to create an encrypt key for XOR cypher.
std::string File_System::create_encrypt_key()
{
    // Flush the buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    print_internal_divider();

    std::string key = get_string("Please enter your Key: ");

    // Get the key, make sure they write it down.
    std::cout << "The key [" << key << "] has been generated successfully." << std::endl;
    std::cout << "MAKE SURE TO WRITE THIS DOWN, IF THE KEY IS LOST, SO IS YOUR DATA" << std::endl;
    std::cout << "If the encrypt key is entered incorrectly, the data will be re-encrypted and therefore lost." << std::endl;

    // Give them time to write it down.
    pause_key();

    // Return the key.
    return key;
}
//! Allow the files to be saved to disk
void File_System::save_to_disk()
{
    // Lock the file
    std::lock_guard<std::mutex> lock(_mutex);
    // Create a file to write to.
    std::ofstream write_file("v_file_system.txt");

    // Check if it is open.
    if (!write_file)
    {
        std::cerr << "Error opening the file for writing." << std::endl;
        return;
    }

    // For every key : value pair in the files.
    for (auto& pair : _files)
    {
        File& file = pair.second;

        write_file << "[START FILE]" << std::endl;

        // Write the files to the new file
        write_file << file.ID << '\n';
        write_file << file.inode.file_ext << '\n';
        write_file << file.inode.file_name << '\n';
        write_file << file.inode.size << '\n';
        write_file << file.contents << '\n';

        // Since permissions is another hasmap to the same.
        for (const auto& perm : file.inode.permissions.current_permissions())
        {
            write_file << perm;
        }

        // Specify the end of file for easy reading.
        write_file << '\n';
        write_file << "[END FILE]" << '\n';
    }

    // This does not have to be here, will close when write_file goes out of scope.
    write_file.close();
}

//! Allow the user to read back their files from the disk
void File_System::read_from_disk()
{
    // Lock from other threads.
    std::lock_guard<std::mutex> lock(_mutex);
    // Open the file on disk.
    std::ifstream read_file("v_file_system.txt");

    // Check if its accessible.
    if (!read_file)
    {
        std::cerr << "Error opening the file for reading. Does it exist?" << std::endl;
        return;
    }

    std::string line;
    // while there is new lines in the read file.
    while (std::getline(read_file, line))
    {
        //? Make sure the read file is valid. This allows user to write their own content in the file also
        if (line == "[START FILE]")
        {
            File file;

            // Read the ID as a string
            std::string id_str;
            std::getline(read_file, id_str);
            // Convert back to int and place back into file.
            file.ID = std::stoi(id_str);

            // Get the file extension and name
            std::getline(read_file, file.inode.file_ext);
            std::getline(read_file, file.inode.file_name);

            // Get the size
            std::string size_str;
            std::getline(read_file, size_str);
            file.inode.size = std::stoi(size_str);

            // Contents get the contents.
            std::getline(read_file, file.contents);

            // Get the permissions
            std::string permissions_str;
            std::getline(read_file, permissions_str);
            file.inode.permissions.load_from_string(permissions_str);

            //? Confirm the correct structure.
            //! This means users can create a file in the .txt without actually opening the program.
            std::getline(read_file, line);
            if (line != "[END FILE]")
            {
                std::cerr << "Malformed file entry detected, skipping.\n";
                continue;
            }

            // Store the loaded files back in the map.
            _files[file.ID] = file;
        }
    }

    read_file.close();
}
