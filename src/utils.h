#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstdlib>

bool is_root();

std::string Inquire_once(std::string question);
std::vector<std::string> Inquire();

bool write_file(std::string, std::string);

int system_call(std::string command);

bool add_executable_to_path(std::string exec_path);