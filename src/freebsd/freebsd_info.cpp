#include "freebsd_info.h"
#include "../shared/unix.h"
#include "../utils.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sys/sysctl.h>

uint64 readSysctl(const std::string& name)
{
    uint64 val;
    size_t size = sizeof(val);
    sysctlbyname(name.c_str(), &val, &size, NULL, 0);

    return val;
}

std::string FreeBSDReadout::kernel()
{
    return unixReadout::kernel();
}

std::string FreeBSDReadout::os()
{
    return unixReadout::osrelease("FreeBSD");
}

std::string FreeBSDReadout::hostname()
{
    return unixReadout::hostname();
}

std::string FreeBSDReadout::username()
{
    return unixReadout::username();
}

std::string FreeBSDReadout::shell()
{
    return unixReadout::shell();
}

const uint64 MB_DIVIDER = 1024ll * 1024ll;

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
    const uint64 bootTime = readSysctl("kern.boottime");
    const auto now = unixNow();

    return (now - bootTime) * 1000ll;
}
