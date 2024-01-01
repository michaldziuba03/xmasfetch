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
    Memory memory() override;
    std::string kernel() override;
    std::string os() override;
    std::string shell() override;
    std::string hostname() override;
    std::string username() override;
    uint64 uptime() override;
};
