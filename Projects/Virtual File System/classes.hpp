#pragma once

#include "includes.hpp"

class Permission
{
   private:
    std::unordered_map<char, bool> _permissions;

   public:
    Permission();
    void print_permission_options();
    std::string current_permissions();
    void change_permission(char perm, bool value);
};
class Inode
{
   public:
    std::string file_name;
    size_t size;
    std::string file_ext;
    std::string available_exts[7];
    Permission permissions;

    Inode();
    void set_metadata();

   private:
    std::string get_ext();
    void print_ext_options();
};
class File
{
   private:
    static int master_counter;

   public:
    int ID;
    Inode inode;
    std::string contents;

    File();
};

class File_System
{
   private:
    std::unordered_map<int, File> _files;
    std::mutex _mutex;

    int get_valid_ID();
    std::string create_encrypt_key();

   public:
    File_System();
    void add_file();
    void remove_file();
    void print_files_data();
    void append_text();
    void overwrite_text();
    void read_text();
    void change_file_permission();
    void print_current_permission();
    bool check_valid_permission(char perm, int id);
    void encrypt_decrypt();
};