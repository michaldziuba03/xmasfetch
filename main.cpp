#include "windows_info.h"
#include "utils.hxx"
#include <string>
#include <iostream>

int main()
{
    Windows win;
    Memory mem = win.memory();

    std::cout << win.username() << "@" << win.hostname() << std::endl;
    std::cout << "OS: " << win.os() << std::endl;
    std::cout << "Kernel: " << win.kernel() << std::endl;
    std::cout << "Memory: " << mem.used << " MB / " << mem.total << " MB" << std::endl;
    std::cout << "Uptime: " << prettyUptime<unsigned long long>(win.uptime()) << std::endl;
}
