#pragma once
#include <string>
#include "../shared/declariations.h"

class LinuxReadout : public SystemReadout {
public:
    Memory memory();
    std::string kernel();
    std::string os();
    std::string hostname();
    std::string username();
    std::string shell();
    uint64 uptime();
};
