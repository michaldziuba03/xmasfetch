#include "ascii.h"
#include <string>
#include <iostream>
#include <sstream>
#include "info.h"

const char* DELIMITER = "   ";

int main()
{
    std::vector<std::string> sysInfo = getInfo();
    std::istringstream f(ASCII);
    std::string line;

    size_t maxLineLen = 0;
    size_t maxLen = 0;

    while (std::getline(f, line)) {
        maxLineLen = std::max(maxLineLen, line.length());
        ++maxLen;
    }

    maxLen = std::max(maxLen, sysInfo.size());

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
