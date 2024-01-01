#pragma once
#include <string>
#include "../shared/declariations.h"

class LinuxReadout : public SystemReadout {
public:
    Memory memory() override;
    std::string kernel() override;
    std::string os() override;
    std::string hostname() override;
    std::string username() override;
    std::string shell() override;
    uint64 uptime() override;
};
