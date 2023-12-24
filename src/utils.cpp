#include "utils.h"
#include <chrono>

std::string formatDuration(unsigned int durCount, const std::string& durName)
{
    if(durCount > 1)
    {
        return std::to_string(durCount) + " " + durName + "s ";
    }

    return std::to_string(durCount) + " " + durName + " ";
}

std::string prettyUptime(unsigned long uptime)
{
    using namespace std::chrono;
    auto ms = milliseconds(uptime);
    auto day = duration_cast<days>(ms);
    auto hour = duration_cast<hours>(ms - day);
    auto min = duration_cast<minutes>(ms - day - hour);

    std::string prettyStr;

    if (day.count())
    {
        prettyStr += formatDuration(day.count(), DUR_DAY);
    }

    if (hour.count())
    {
        prettyStr += formatDuration(hour.count(), DUR_HOUR);
    }

    if (min.count())
    {
        prettyStr += formatDuration(min.count(), DUR_MINUTE);
    }
    else if (prettyStr.empty())
    {
        auto sec = duration_cast<seconds>(ms);
        prettyStr += formatDuration(sec.count(), DUR_SECOND);
    }

    return prettyStr;
}

std::string prettyMemory(unsigned int used, unsigned int total)
{
    return std::to_string(used) + " MB / " + std::to_string(total) + " MB";
}
