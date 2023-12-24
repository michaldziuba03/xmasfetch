#pragma once
#include <string>

#define C_RESET "\x1b[0m"
#define C_BOLD "\x1b[1m"
#define C_BLACK "\x1b[30m"
#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_BLUE "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN "\x1b[36m"
#define C_WHITE "\x1b[37m"

#ifdef _WIN32
void win32_enableAnsi();
#endif
std::string colorize(std::string);
std::string termColors();
