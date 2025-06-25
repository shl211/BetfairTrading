#include "time_range_result.h"
#include <ostream>

namespace BetfairAPI::BettingType {

    TimeRangeResult::TimeRangeResult(TimeRange time_range, int market_count)
        : time_range_(std::move(time_range)), market_count_(market_count) {}
    
    std::ostream& operator<<(std::ostream& os, const TimeRangeResult& obj) {
        os << "TimeRangeResult{time_range=" << obj.time_range_ << ", market_count=" << obj.market_count_ << "}";
        return os;
    }

    TimeRange TimeRangeResult::getTimeRange() {
        return time_range_;
    }

    int TimeRangeResult::getMarketCount() {
        return market_count_;
    }
}