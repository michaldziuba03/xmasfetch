#include "unix.h"
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

std::string unix_username()
{
    uid_t uid = getuid();
    passwd *pw = getpwuid(uid);

    return pw->pw_name;
}

std::string unix_hostname()
{
    utsname os{};
    int err = uname(&os);
    if (err == -1)
    {
        return "unknown";
    }

    return os.nodename;
}

std::string unix_shell()
{
    uid_t uid = getuid();
    passwd *pw = getpwuid(uid);

    return pw->pw_shell;
}

std::string unix_kernel()
{
    utsname os{};
    int err = uname(&os);
    if (err == -1)
    {
        return "unknown";
    }

    return os.release;
}
