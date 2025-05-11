#ifndef TIME_GRANULARITY_H
#define TIME_GRANULARITY_H

#include <string_view>

namespace BetfairAPI {
    enum class TimeGranularity {
        DAYS,
        HOURS,
        MINUTES
    };

    constexpr std::string_view timeGranularityToString(const TimeGranularity& g) {
        switch(g) {
            case TimeGranularity::DAYS: return "DAYS"; 
            case TimeGranularity::HOURS: return "HOURS"; 
            case TimeGranularity::MINUTES: return "MINUTES"; 
            default: return "UNKNOWN";
        }
    }
}

#endif