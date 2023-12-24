#include "colors.h"

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

std::string parseColor(std::string text)
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
                size_t colorIdx = text[offset] - '0';
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
