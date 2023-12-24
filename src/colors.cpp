#include "colors.h"
#include <iostream>

std::string colors[] = {
        "\x1b[32;1m",
        "\x1b[31;1m",
        "\x1b[33;1m",
        "\x1b[34;1m",
        "\x1b[35;1m",
        "\x1b[39;1m",
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
