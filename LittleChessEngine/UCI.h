#pragma once
#include <string>
#include <iostream>
#include "Search.h"
#define COMMAND_LENGTH 511

void command_loop();
void parse_command(char* command, std::string& cmd, std::string& params);
void execute_command(char* command);