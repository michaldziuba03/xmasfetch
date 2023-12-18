#include "windows_info.h"
#include "wmi.hxx"
#include <iostream>
#include <windows.h>
#include <format>
#include <Lmcons.h>

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

std::string getWindowsVersion()
{
    QueryResult res = SendWmiQuery("SELECT Caption, Version FROM Win32_OperatingSystem");
    res.Next();
    std::cout << "OS: " << res.GetStr(L"Caption") << std::endl;
    std::cout << "Kernel: " << res.GetStr(L"Version") << std::endl;
    return res.GetStr(L"Caption");
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
