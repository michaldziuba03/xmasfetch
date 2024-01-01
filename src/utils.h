#pragma once
#include <string>
#include "shared/declariations.h"

#define DUR_DAY "day"
#define DUR_HOUR "hour"
#define DUR_MINUTE "minute"
#define DUR_SECOND "second"

uint64 unixNow();
std::string formatDuration(unsigned int, const std::string&);
std::string prettyUptime(uint64);
std::string prettyMemory(unsigned int, unsigned int);
