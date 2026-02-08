#pragma once
#include <map>
#include <string>

extern std::map<std::string, void(*)()> command_table;

void InitCommands();
