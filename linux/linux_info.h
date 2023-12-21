#pragma once
#include <string>

struct Memory
{
    unsigned long total;
    unsigned long used;
};

class Linux
{
private:
public:
    Memory memory();
    std::string kernel();
    std::string os();
    std::string hostname();
    std::string username();
    unsigned long long uptime();
};
