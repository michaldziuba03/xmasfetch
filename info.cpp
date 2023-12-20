#include "info.h"
#include <vector>
#include "utils.hxx"

#ifdef _WIN32
#include "windows/windows_info.h"
#endif

#ifdef __linux__
#include "linux/linux_info.h"
#endif

std::vector<std::string> getInfo()
{
    std::vector<std::string> sysInfo;

#ifdef _WIN32
    Windows info;
    Memory mem = info.memory();
#endif

#ifdef __linux__
    Linux info;
    Memory mem = info.memory();
#endif

    std::string nameAndHost = info.username() + "@" + info.hostname();
    sysInfo.push_back(nameAndHost);
    sysInfo.push_back(separator("-", nameAndHost.length()));
    sysInfo.push_back("OS: " + info.os());
    sysInfo.push_back("Kernel: " + info.kernel());
    sysInfo.push_back("Memory: " + prettyMemory(mem.used, mem.total));
    sysInfo.push_back("Uptime: " + prettyUptime(info.uptime()));

    return sysInfo;
}
