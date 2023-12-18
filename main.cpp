#include "windows_info.h"
#include <string>
#include <iostream>

int main()
{
    std::string hostname = getHostname();
    std::string os = getWindowsVersion();

    std::cout << os << std::endl;
    std::cout << hostname << std::endl;
    return 0;
}
