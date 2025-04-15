#pragma once

#include "includes.hpp"

//* Forward declaration
class File_System;

//! =====================
//! All functions are explained in classes.cpp
//! =====================

// Permission class
class Permission
{
   private:
    std::unordered_map<char, bool> _permissions;

   public:
    Permission();
    void print_permission_options();
    std::string current_permissions();
    void change_permission(char perm, bool value);
    void load_from_string(const std::string& perm_string);
};
// Inode class
class Inode
{
   public:
    // The inode data for each file.
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
// File class
class File
{
   private:
    // For creating unique ID's
    static int master_counter;

   public:
    // Each file will have this data.
    int ID;
    Inode inode;
    std::string contents;

    File();
};
// File_System class. This is the main class we will be working with.
class File_System
{
   private:
    //! Hasmap and mutex lock (for threads.)
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
    void save_to_disk();
    void read_from_disk();
};