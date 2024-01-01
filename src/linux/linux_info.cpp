#include "linux_info.h"
#include "../shared/unix.h"
#include <string>
#include <fstream>

std::string LinuxReadout::kernel()
{
    std::string kernel;
    std::ifstream osrelease("/proc/sys/kernel/osrelease");
    if (osrelease.is_open())
    {
        std::getline(osrelease, kernel);
        osrelease.close();
    }

    return kernel;
}

std::string LinuxReadout::os()
{
    return unixReadout::osrelease("Linux");
};

std::string LinuxReadout::hostname()
{
    return unixReadout::hostname();
}

std::string LinuxReadout::username()
{
    return unixReadout::username();
}

std::string LinuxReadout::shell()
{
    return unixReadout::shell();
}

const uint64 MB_DIVIDER = 1024ll;

Memory LinuxReadout::memory()
{
    std::ifstream memInfo("/proc/meminfo");
    if (!memInfo.is_open())
    {
        return { 0, 0 };
    }

    uint64 total = 0;
    uint64 available = 0;

    while(memInfo.good())
    {
        std::string key;
        memInfo >> key;

        if (key == "MemTotal:")
        {
            memInfo >> total;
        }
        else if (key == "MemAvailable:")
        {
            memInfo >> available;
        }

        if (total && available)
        {
            break;
        }
    }

    memInfo.close();

    return
    {
        total / MB_DIVIDER,
        (total - available) / MB_DIVIDER,
    };
}

uint64 LinuxReadout::uptime()
{
    std::ifstream uptimeFile("/proc/uptime");
    uint64 uptime = 0;

    if (uptimeFile.is_open())
    {
        uptimeFile >> uptime;
        uptimeFile.close();
    }

    return uptime * 1000ll; // linux shows uptime in seconds
}
