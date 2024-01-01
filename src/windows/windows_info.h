#pragma once
#include "../shared/declariations.h"
#include <Windows.h>
#include <string>

class WindowsReadout : public SystemReadout
{
    std::string architecture;
    std::string caption;
    std::string version;
public:
    WindowsReadout();
    Memory memory();
    std::string kernel();
    std::string os();
    std::string shell();
    std::string hostname();
    std::string username();
    uint64 uptime();
};
