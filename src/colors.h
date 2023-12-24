#pragma once

#define C_RESET "\x1b[0m"
#define C_BLACK "\x1b[30;1m"
#define C_RED "\x1b[31;1m"
#define C_GREEN "\x1b[32;1m"
#define C_YELLOW "\x1b[33;1m"
#define C_BLUE "\x1b[34;1m"
#define C_MAGENTA "\x1b[35;1m"
#define C_CYAN "\x1b[36;1m"
#define C_WHITE "\x1b[37;1m"

#include <string>

std::string parseColor(std::string);
