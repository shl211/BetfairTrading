#pragma once

#include <ostream>

#include "BetfairAPI/betting_enum/time_granularity.hpp"
#include "BetfairAPI/betting_type/time_range.h"

namespace BetfairAPI::BettingType {
    struct TimeRangeResult {
        TimeRange timeRange;
        int marketCount = 0;
    };

    inline bool operator==(const TimeRangeResult& lhs,const TimeRangeResult& rhs) {
        return lhs.timeRange == rhs.timeRange && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const TimeRangeResult& lhs,const TimeRangeResult& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os,const TimeRangeResult& trr) {
        os << "Time range result: " << trr.timeRange << " with market count " << trr.marketCount;
        return os;
    }
}