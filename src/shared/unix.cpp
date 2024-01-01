#include "unix.h"
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include <fstream>

namespace unixReadout
{
    // according to manual: "Do not pass the returned pointer to free()"
    passwd* getPasswd()
    {
        uid_t uid = getuid();
        passwd *pw = getpwuid(uid);

        return pw;
    }

    utsname getUname()
    {
        utsname os{};
        uname(&os);

        return os;
    }

    std::string osrelease(const std::string& fallback)
    {
        const std::string PRETTY_NAME = "PRETTY_NAME=";

        std::ifstream release("/etc/os-release");
        if (!release.is_open())
        {
            return fallback;
        }

        std::string os;
        std::string line;
        while(std::getline(release, line) && os.empty())
        {
            if (!line.starts_with(PRETTY_NAME))
            {
                continue;
            }

            os = line.substr(PRETTY_NAME.length());
            if (os.starts_with("\""))
            {
                os = os.substr(1);
            }

            if (os.ends_with("\""))
            {
                os.pop_back();
            }
        }

        release.close();

        if (os.empty())
        {
            return fallback;
        }

        return os;
    }

    std::string username()
    {
        return getPasswd()->pw_name;
    }

    std::string hostname()
    {
        return getUname().nodename;
    }

    std::string shell()
    {
        return getPasswd()->pw_shell;
    }

    std::string kernel()
    {
        return getUname().release;
    }
}
