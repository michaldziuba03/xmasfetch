#define NOMINMAX
#include "ascii.h"
#include "colors.h"
#include <string>
#include <iostream>
#include "info.h"
#include <regex>

#ifdef _WIN32

#include <Windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

void activateVirtualTerminal()
{
    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
}
#endif

const char* RESET_COLOR = "\033[0m";
const char* DELIMITER = "  ";


const std::regex colorExp("\\$[0-9]");
size_t getLineWidth(const std::string& line)
{
    return std::regex_replace(line, colorExp, "").length();
}

int main()
{
#ifdef _WIN32
    activateVirtualTerminal();
#endif
    std::vector<std::string> sysInfo = getInfo();
    const size_t logoWidth = getLineWidth(ASCII_TREE[0]);
    const size_t maxHeight = std::max(ASCII_TREE_SIZE, sysInfo.size());

    for (int i = 0; i < maxHeight; ++i)
    {
        if (i < ASCII_TREE_SIZE)
        {
            std::cout << parseColor(ASCII_TREE[i]);
        } else {
            std::cout << std::string(logoWidth, ' ');
        }

        if (i < sysInfo.size())
        {
            std::cout << RESET_COLOR << DELIMITER << sysInfo[i];
        }

        std::cout << parseColor("$5") << std::endl;
    }
}
