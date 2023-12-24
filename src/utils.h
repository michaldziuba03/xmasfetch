#pragma once
#include <string>

#define DUR_DAY "day"
#define DUR_HOUR "hour"
#define DUR_MINUTE "minute"
#define DUR_SECOND "second"

std::string formatDuration(unsigned int, const std::string&);
std::string prettyUptime(unsigned long);
std::string prettyMemory(unsigned int, unsigned int);
