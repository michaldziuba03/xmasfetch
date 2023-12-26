#pragma once
#include <string>

struct Memory
{
    unsigned long total;
    unsigned long used;
};


class FreeBSD
{
public:
    Memory memory();
    std::string kernel();
    std::string os();
    std::string hostname();
    std::string username();
    std::string shell();
    unsigned long long uptime();
};
