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
    return unix_osrelease("Linux");
};

std::string LinuxReadout::hostname()
{
    return unix_hostname();
}


std::string LinuxReadout::username()
{
    return unix_username();
}

std::string LinuxReadout::shell()
{
    return unix_shell();
}

const int MB_DIVIDER = 1024;

Memory LinuxReadout::memory()
{
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open())
    {
        return { 0, 0 };
    }

    unsigned long total = 0;
    unsigned long available = 0;

    while(meminfo.good())
    {
        std::string key;
        meminfo >> key;

        if (key == "MemTotal:")
        {
            meminfo >> total;
        }
        else if (key == "MemAvailable:")
        {
            meminfo >> available;
        }

        if (total && available)
        {
            break;
        }
    }

    meminfo.close();

    return
    {
        total / MB_DIVIDER,
        (total - available) / MB_DIVIDER,
    };
}

uint64 LinuxReadout::uptime()
{
    std::ifstream uptimeFile("/proc/uptime");
    unsigned long long uptime = 0;

    if (uptimeFile.is_open())
    {
        uptimeFile >> uptime;
        uptimeFile.close();
    }

    return uptime * 1000l; // linux shows uptime in seconds
}
