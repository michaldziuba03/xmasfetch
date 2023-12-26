#include "linux_info.h"
#include "../shared/unix.h"
#include <string>
#include <fstream>

std::string Linux::kernel()
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

std::string Linux::os()
{
    const std::string PRETTY_NAME = "PRETTY_NAME=";

    std::ifstream release("/etc/os-release");
    if (!release.is_open())
    {
        return "Unknown Linux";
    }

    std::string os;
    std::string line;
    while(std::getline(release, line) && os.empty())
    {
        if (!line.starts_with(PRETTY_NAME))
        {
            continue;
        }

        os = line.substr(PRETTY_NAME.length());
        if (os.starts_with("\""))
        {
            os = os.substr(1);
        }

        if (os.ends_with("\""))
        {
            os.pop_back();
        }
    }

    release.close();

    return os;
};

std::string Linux::hostname()
{
    return unix_hostname();
}


std::string Linux::username()
{
    return unix_username();
}

std::string Linux::shell()
{
    return unix_shell();
}

const int MB_DIVIDER = 1024;

Memory Linux::memory()
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

unsigned long long Linux::uptime()
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
