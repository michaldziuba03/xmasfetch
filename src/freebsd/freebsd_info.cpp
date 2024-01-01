#include "freebsd_info.h"
#include "../shared/unix.h"
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sys/sysctl.h>

unsigned long long readSysctl(const std::string& name)
{
    unsigned long long val;
    size_t size = sizeof(val);
    sysctlbyname(name.c_str(), &val, &size, NULL, 0);

    return val;
}

unsigned long unixNow()
{
    const auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(timeEpoch).count();
}


std::string FreeBSDReadout::kernel()
{
    return unix_kernel();
}

std::string FreeBSDReadout::os()
{
    return unix_osrelease("FreeBSD");
}

std::string FreeBSDReadout::hostname()
{
    return unix_hostname();
}

std::string FreeBSDReadout::username()
{
    return unix_username();
}

std::string FreeBSDReadout::shell()
{
    return unix_shell();
}

const unsigned long long MB_DIVIDER = 1024ll * 1024ll;

Memory FreeBSDReadout::memory()
{
    unsigned long long memTotal = readSysctl("hw.physmem");
    unsigned long long memAvailable = readSysctl("hw.usermem");

    return {
        memTotal / MB_DIVIDER,
        long(memTotal - memAvailable) / MB_DIVIDER,
    };
}

uint64 FreeBSDReadout::uptime()
{
    unsigned long long bootTime = readSysctl("kern.boottime");
    const auto now = unixNow();

    return (now - bootTime) * 1000;
}
