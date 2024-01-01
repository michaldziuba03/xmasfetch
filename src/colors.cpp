#include "colors.h"
#ifdef _WIN32
#include <Windows.h>
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

void win32_enableANSI()
{
    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
}
#endif

std::string colors[] = {
        C_RESET,
        C_BLACK,
        C_RED,
        C_GREEN,
        C_YELLOW,
        C_BLUE,
        C_MAGENTA,
        C_CYAN,
        C_WHITE,
};

inline unsigned int charToDigit(char c)
{
    return c - '0';
}

// replace color placeholder like $1. $2 with ansi sequence
std::string colorize(std::string text)
{
    std::string coloredText;
    int offset = 0;
    while (offset < text.length())
    {
        if (text[offset] == '$')
        {
            ++offset;
            if (text[offset] >= '0' && text[offset] <= '9')
            {
                size_t colorIdx = charToDigit(text[offset]);
                coloredText += colors[colorIdx];
                ++offset;
                continue;
            }
        }

        coloredText.push_back(text[offset]);
        ++offset;
    }

    return coloredText;
}

std::string termColors()
{
    std::string ansiSequences;

    for (int i = 40; i < 48; ++i)
    {
        ansiSequences += ("\x1b[" + std::to_string(i) + "m   ");
    }

    return ansiSequences + C_RESET;
}
