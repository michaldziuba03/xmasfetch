#pragma once
#include <iostream>
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
        prettyStr.append(formatDuration(day.count(), "day"));
    }

    if (hour.count())
    {
        prettyStr.append(formatDuration(hour.count(), "hour"));
    }

    if (min.count())
    {
        prettyStr.append(formatDuration(min.count(), "minute"));
    }
    else if (prettyStr.empty())
    {
        auto sec = duration_cast<seconds>(ms);
        prettyStr.append(formatDuration(sec.count(), "second"));
    }

    return prettyStr;
}

inline std::string prettyMemory(unsigned int used, unsigned int total)
{
    return std::to_string(used) + " MB / " + std::to_string(total) + "MB";
}

std::string separator(const std::string&  sym, unsigned int len)
{
    std::string sep;

    for (int i = 0; i < len; ++i)
    {
        sep.append(sym);
    }

    return sep;
}
