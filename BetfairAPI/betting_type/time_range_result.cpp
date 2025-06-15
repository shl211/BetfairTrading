#include "time_range_result.h"

namespace BetfairAPI::BettingType {

    TimeRangeResult::TimeRangeResult(TimeRange time_range, int market_count)
        : time_range_(std::move(time_range)), market_count_(market_count) {}
    
    TimeRange TimeRangeResult::getTimeRange() {
        return time_range_;
    }

    int TimeRangeResult::getMarketCount() {
        return market_count_;
    }
}