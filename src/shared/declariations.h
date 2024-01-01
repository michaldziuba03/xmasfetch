#pragma once
#include <string>

typedef signed int int32;
typedef signed long long int64;
typedef unsigned long long uint64;

struct Memory
{
    uint64 total;
    uint64 used;
};

class SystemReadout
{
public:
    virtual Memory memory() = 0;
    virtual std::string kernel() = 0;
    virtual std::string os() = 0;
    virtual std::string hostname() = 0;
    virtual std::string username() = 0;
    virtual std::string shell() = 0;
    virtual uint64 uptime() = 0;
};
