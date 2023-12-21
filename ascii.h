#pragma once
#include <string>
#include <sstream>

const char* ASCII = R"(      /\
     /\*\
    /\O\*\
   /*/\/0/\
  /\O\/\*\/\
 /\*\/\*\/\/\
/\O\/\/*/\/O/\
    \____/
)";

struct AsciiLogo
{
public:
    size_t width = 0;
    size_t height = 0;

    explicit AsciiLogo(const std::string& ascii)
    {
        std::istringstream logo(ascii);
        std::string line;

        while (std::getline(logo, line))
        {
            width = std::max(width, line.length());
            ++height;
        }
    }
};
