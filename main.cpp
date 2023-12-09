#include <iostream>
#include <windows.h>
#include <format>
#include <Lmcons.h>

struct Memory
{
    ULONGLONG total;
    ULONGLONG used;
};

const int MB_DIVIDER = 1024 * 1024;

Memory getMemory()
{
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);

    ULONGLONG total = ms.ullTotalPhys / MB_DIVIDER;
    ULONGLONG used = (ms.ullTotalPhys - ms.ullAvailPhys) / MB_DIVIDER;

    return
    {
        total,
        used,
    };
}

std::string getKernel()
{
    OSVERSIONINFO os{};
    os.dwOSVersionInfoSize = sizeof(os);
    GetVersionEx(&os);

    return std::format("{}.{}.{}", os.dwMajorVersion, os.dwMinorVersion, os.dwBuildNumber);
}

// TODO: switch to WMI query
std::string getWindowsVersion()
{
    OSVERSIONINFO os{};
    os.dwOSVersionInfoSize = sizeof(os);
    GetVersionEx(&os);

    DWORD majorVer = os.dwMajorVersion;
    DWORD minorVer = os.dwMinorVersion;
    DWORD buildVer = os.dwBuildNumber;

    if (majorVer == 5 && minorVer == 1)
    {
        return "Windows XP";
    }

    if (majorVer == 6 && minorVer == 0)
    {
        return "Windows Vista";
    }

    if (majorVer == 6 && minorVer == 1)
    {
        return "Windows 7";
    }

    if (majorVer == 6 && minorVer == 2)
    {
        return "Windows 8";
    }

    if (majorVer == 6 && minorVer == 3)
    {
        return "Windows 8.1";
    }

    if (majorVer == 10)
    {
        if (buildVer >= 22000)
        {
            return "Windows 11";
        }

        return "Windows 10";
    }

    return "Windows"; // return generic name for unknown or unsupported Windows versions
}

const int NAME_SIZE = UNLEN+1;

std::string getHostname()
{
    char hostname[NAME_SIZE];
    DWORD size = NAME_SIZE;
    GetComputerName(hostname, &size);

    return hostname;
}

std::string getUsername()
{
    char username[NAME_SIZE];
    DWORD size = NAME_SIZE;
    GetUserName(username, &size);

    return username;
}

ULONGLONG getUptime()
{
    return GetTickCount64();
}

int main()
{
    std::string username = getUsername();
    std::string hostname = getHostname();
    std::string os = getWindowsVersion();
    std::string kernel = getKernel();
    Memory memory = getMemory();
    ULONGLONG uptime = getUptime();

    std::cout << username << "@" << hostname << std::endl;
    std::cout << "OS: " << os << std::endl;
    std::cout << "Kernel: " << kernel << std::endl;
    std::cout << "Memory: " << memory.used << " MB / " << memory.total << " MB" << std::endl;
    std::cout << "Uptime: " << uptime << " ms" << std::endl;

    return 0;
}
