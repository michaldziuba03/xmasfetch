#include "windows_info.h"
#include "wmi.hxx"
#include <Windows.h>
#include <format>
#include <lmcons.h>

Windows::Windows()
{
    QueryResult res = SendWmiQuery("SELECT Caption, Version, OSArchitecture FROM Win32_OperatingSystem");
    res.Next();

    caption = res.GetStr(L"Caption");
    architecture = res.GetStr(L"OSArchitecture");
    version = res.GetStr(L"Version");
}

const int MB_DIVIDER = 1024 * 1024;

Memory Windows::memory()
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

std::string Windows::kernel()
{
    return version;
}

std::string Windows::os()
{
    return std::format("{} [{}]", caption, architecture);
}

const int NAME_SIZE = UNLEN+1;

std::string Windows::shell()
{
    return "";
}

std::string Windows::hostname()
{
    char hostname[NAME_SIZE];
    DWORD size = NAME_SIZE;
    GetComputerName(hostname, &size);

    return hostname;
}

std::string Windows::username()
{
    char username[NAME_SIZE];
    DWORD size = NAME_SIZE;
    GetUserName(username, &size);

    return username;
}

unsigned long long Windows::uptime()
{
    return GetTickCount64();
}
