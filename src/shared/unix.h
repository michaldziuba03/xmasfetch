#pragma once
#include <string>

namespace unixReadout {
    std::string hostname();
    std::string hostname();
    std::string username();
    std::string shell();
    std::string kernel();
    std::string osrelease(const std::string&);
}
