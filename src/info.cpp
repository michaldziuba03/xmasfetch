#include "info.h"
#include "utils.h"
#include "colors.h"
#include <vector>

#ifdef _WIN32
#include "windows/windows_info.h"
#endif

#ifdef __linux__
#include "linux/linux_info.h"
#endif

#ifdef __FreeBSD__
#include "freebsd/freebsd_info.h"
#endif

#define EMPTY_LINE " "

std::string keyValue(const std::string& key, const std::string& value)
{
    return C_BOLD C_GREEN + key + C_RESET + ": " + C_YELLOW + value;
}

std::vector<std::string> fetchInfo()
{
    std::vector<std::string> sysInfo;

#ifdef _WIN32
    WindowsReadout info;
#endif

#ifdef __linux__
    LinuxReadout info;
#endif

#ifdef __FreeBSD__
    FreeBSDReadout info;
#endif
    Memory mem = info.memory();
    const std::string username = info.username();
    const std::string hostname = info.hostname();
    const size_t separatorLen = username.length() + hostname.length() + 1;

    sysInfo.push_back(C_BOLD C_RED + username + C_RESET C_BOLD "@" + C_RED + hostname);
    sysInfo.push_back(C_BOLD C_YELLOW + std::string (separatorLen, '-'));
    sysInfo.push_back(keyValue("OS", info.os()));
    sysInfo.push_back(keyValue("Kernel", info.kernel()));
    std::string shell = info.shell();
    if (!shell.empty())
    {
        sysInfo.push_back(keyValue("Shell", shell));
    }

    sysInfo.push_back(keyValue("Uptime", prettyUptime(info.uptime())));
    sysInfo.push_back(keyValue("Memory", prettyMemory(mem.used, mem.total)));
    sysInfo.emplace_back(EMPTY_LINE);
    sysInfo.push_back(termColors());

    return sysInfo;
}
