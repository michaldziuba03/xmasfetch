#ifndef XMASFETCH_WINDOWS_INFO_H
#define XMASFETCH_WINDOWS_INFO_H

#include <windows.h>
#include <string>

struct Memory
{
    ULONGLONG total;
    ULONGLONG used;
};

Memory getMemory();
std::string getKernel();
std::string getWindowsVersion();
std::string getHostname();
std::string getUsername();
ULONGLONG getUptime();

#endif //XMASFETCH_WINDOWS_INFO_H
