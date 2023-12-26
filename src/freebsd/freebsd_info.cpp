#include "freebsd_info.h"
#include "../shared/unix.h"
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sys/sysctl.h>

std::string FreeBSD::kernel()
{
    return unix_kernel();
}

std::string FreeBSD::os()
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

std::string FreeBSD::hostname()
{
    return unix_hostname();
}


std::string FreeBSD::username()
{
    return unix_username();
}

std::string FreeBSD::shell()
{

    return unix_shell();
}

unsigned long long readSysctl(std::string name)
{
    unsigned long long val;
    size_t size = sizeof(val);
    sysctlbyname(name.c_str(), &val, &size, NULL, 0);

    return val;

}

const unsigned long long MB_DIVIDER = 1024ll * 1024ll;

Memory FreeBSD::memory()
{
    unsigned long long memTotal = readSysctl("hw.physmem");
    unsigned long long memAvailable = readSysctl("hw.usermem");

    return
            {
                    memTotal / MB_DIVIDER,
                    long(memTotal - memAvailable) / MB_DIVIDER,
            };
}

unsigned long unixNow()
{
    const auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(timeEpoch).count();
}

unsigned long long FreeBSD::uptime()
{
    unsigned long long bootTime = readSysctl("kern.boottime");
    const auto now = unixNow();

    return (now - bootTime) * 1000;
}
