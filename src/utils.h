#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <ofstream>

bool is_root();

std::string Inquire_once(std::string question);
std::vector<std::string> Inquire();

bool write_file(std::string, std::string);

