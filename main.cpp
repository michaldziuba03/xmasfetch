#include "ascii.h"
#include <string>
#include <iostream>
#include <sstream>
#include "info.h"

const char* DELIMITER = "   ";

int main()
{
    std::vector<std::string> sysInfo = getInfo();
    auto logo = AsciiLogo(ASCII);
    size_t maxHeight = std::max(logo.height, sysInfo.size());

    std::istringstream logoStream(ASCII);
    std::string line;

    for (int i = 0; i < maxHeight; ++i)
    {
        if(logoStream.good())
        {
            std::getline(logoStream, line);
            std::cout << line << std::string(logo.width - line.length(), ' ');
        } else {
            std::cout << std::string(logo.width, ' ');
        }

        if (i < sysInfo.size())
        {
            std::cout << DELIMITER << sysInfo[i];
        }

        std::cout << std::endl;
    }
}
