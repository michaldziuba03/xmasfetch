#include "info.h"
#include <vector>
#include "utils.hxx"
#include "colors.h"

#ifdef _WIN32
#include "windows/windows_info.h"
#endif

#ifdef __linux__
#include "linux/linux_info.h"
#endif

std::string keyValue(const std::string& key, const std::string& value)
{
    return parseColor("$3"+key+"$0: $4" + value);
}

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

    const std::string username = info.username();
    const std::string hostname = info.hostname();
    const size_t separatorLen = username.length() + hostname.length() + 1;

    std::string nameAndHost = parseColor("$2" + info.username() + "$0@$2" + info.hostname());
    sysInfo.push_back(nameAndHost);
    sysInfo.push_back(parseColor("$4" + std::string (separatorLen, '-')));
    sysInfo.push_back(keyValue("OS", info.os()));
    sysInfo.push_back(keyValue("Kernel", info.kernel()));
    std::string shell = info.shell();
    if (!shell.empty())
    {
        sysInfo.push_back(keyValue("Shell", shell));
    }

    sysInfo.push_back(keyValue("Uptime", prettyUptime(info.uptime())));
    sysInfo.push_back(keyValue("Memory", prettyMemory(mem.used, mem.total)));

    std::string ansiColors;

    for (int i = 40; i < 48; ++i)
    {
        ansiColors += ("\x1b[" + std::to_string(i) + "m   ");
    }

    sysInfo.emplace_back(" ");
    sysInfo.push_back(ansiColors + "\x1b[49m");

    return sysInfo;
}
