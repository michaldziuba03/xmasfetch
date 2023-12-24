#define NOMINMAX
#include "ascii.h"
#include "colors.h"
#include <string>
#include <iostream>
#include "info.h"
#include <regex>

#define DELIMITER "  "

const std::regex colorExp("\\$[0-9]"); // match $1, $2...$9

inline size_t getLineWidth(const std::string& line)
{
    // remove color placeholders like $1, $2...$9 from string and return "real" length
    return std::regex_replace(line, colorExp, "").length();
}

int main()
{
#ifdef _WIN32
    win32_enableAnsi();
#endif
    std::vector<std::string> sysInfo = fetchInfo();
    const size_t logoWidth = getLineWidth(ASCII_TREE[0]);
    const size_t maxHeight = std::max(ASCII_TREE_SIZE, sysInfo.size());

    for (int i = 0; i < maxHeight; ++i)
    {
        if (i < ASCII_TREE_SIZE)
        {
            std::cout << C_BOLD << colorize(ASCII_TREE[i]);
        } else {
            std::cout << std::string(logoWidth, ' ');
        }

        if (i < sysInfo.size())
        {
            std::cout << C_RESET << DELIMITER << sysInfo[i];
        }

        std::cout << C_RESET << std::endl;
    }
}
