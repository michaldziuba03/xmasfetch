#include "windows_info.h"
#include "utils.hxx"
#include "ascii.h"
#include <string>
#include <iostream>

const char* DELIMITER = "   ";

int main()
{
    Windows win;
    Memory mem = win.memory();

    std::vector<std::string> sysInfo;

    std::string nameAndHost = std::format("{}@{}", win.username(), win.hostname());
    sysInfo.push_back(nameAndHost);
    sysInfo.push_back(separator("-", nameAndHost.length()));
    sysInfo.push_back(std::format("OS: {}", win.os()));
    sysInfo.push_back(std::format("Kernel: {}", win.kernel()));
    sysInfo.push_back(std::format("Memory: {}", prettyMemory(mem.used, mem.total)));
    sysInfo.push_back(std::format("Uptime: {}", prettyUptime<unsigned long long>(win.uptime())));

    std::istringstream f(ASCII);
    std::string line;

    size_t maxLineLen = 0;
    size_t maxLen = 0;

    while (std::getline(f, line)) {
        maxLineLen = max(maxLineLen, line.length());
        ++maxLen;
    }

    maxLen = max(maxLen, sysInfo.size());

    std::istringstream f2(ASCII);
    for (int i = 0; i < maxLen; ++i)
    {
        std::string buffLine = std::string(maxLineLen, ' ');
        if(std::getline(f2, line))
        {
            buffLine.replace(0, line.length(), line);
        }

        if (i < sysInfo.size())
        {
            buffLine.append(DELIMITER);
            buffLine.append(sysInfo[i]);
        }

        std::cout << buffLine << std::endl;
    }
}
