#include "linux_info.h"
#include <string>

std::string Linux::kernel()
{
    return "6.0.0";
}

std::string Linux::os()
{
    return "Unknown Linux [64-bits]";
};

std::string Linux::hostname()
{
    return "archbox";
}

std::string Linux::username()
{
    return "mchl";
}

Memory Linux::memory()
{
    return
    {
        32000,
        4000,
    };
}

unsigned long long Linux::uptime()
{
    return 50 * 1000;
}
