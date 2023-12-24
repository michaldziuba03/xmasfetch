#pragma once
#include <Windows.h>
#include <string>

struct Memory
{
    ULONGLONG total;
    ULONGLONG used;
};

class Windows
{
    std::string architecture;
    std::string caption;
    std::string version;
public:
    Windows();
    Memory memory();
    std::string kernel();
    std::string os();
    std::string shell();
    std::string hostname();
    std::string username();
    unsigned long long uptime();
};
