#pragma once
#include <iostream>
#include <chrono>
#include <format>

std::string formatDuration(int durCount, const std::string& durName)
{
    if(durCount > 1) {
        return std::format("{} {}s ", durCount, durName);
    }

    return std::format("{} {} ", durCount, durName);
}

template<typename T>
std::string prettyUptime(T uptime)
{
    using namespace std::chrono;
    auto ms = milliseconds(uptime);
    auto day = duration_cast<days>(ms);
    auto hour = duration_cast<hours>(ms - day);
    auto min = duration_cast<minutes>(ms - day - hour);

    std::string prettyStr;

    if (day.count()) {
        prettyStr.append(formatDuration(day.count(), "day"));
    }

    if (hour.count()) {
        prettyStr.append(formatDuration(hour.count(), "hour"));
    }

    if (min.count()) {
        prettyStr.append(formatDuration(min.count(), "minute"));
    }

    return prettyStr;
}
