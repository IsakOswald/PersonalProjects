#pragma once

#include "includes.hpp"

//? Function decs.
std::string get_string(const std::string& prompt);
int get_int(const std::string& prompt);
double get_double(const std::string& prompt);
bool get_bool(const std::string& prompt);
char get_char(const std::string& prompt);
void print_divider(std::string title);
void print_internal_divider();
void clear_screen();
void pause_timer();
void pause_key();
void loading_animation(int iters);
void anti_debug_ptrace();