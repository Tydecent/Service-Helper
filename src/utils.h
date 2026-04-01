#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

bool is_root();

std::string Inquire_once(std::string question);
std::vector<std::string> Inquire();

bool write_file(std::string, std::string);

int system_call(std::string command);

int check_exec(std::string exec_path);

bool add_executable_to_path(std::string exec_path);

bool check_shebang(std::string exec_path);

bool check_file_exists(std::string exec_path);

bool check_ELF_magicnum(std::string exec_path);

std::string get_file_ext(std::string exec_path);

std::string get_file_type(std::string exec_path);

bool Inquire_add_shebang(std::string file_type);

bool add_shebang(std::string exec_path, std::string file_type);

void effective_service(std::string service_name);

std::string get_absolute_path(std::string path);