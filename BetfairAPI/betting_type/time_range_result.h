#pragma once

#include "time_range.h"

namespace BetfairAPI::BettingType {
    class TimeRangeResult {
        public:
            TimeRangeResult(TimeRange time_range,int market_count);
            TimeRangeResult() = default;
            ~TimeRangeResult() = default;
            TimeRangeResult(const TimeRangeResult&) = default;
            TimeRangeResult(TimeRangeResult&&) noexcept = default;
            TimeRangeResult& operator=(const TimeRangeResult&) = default;
            TimeRangeResult& operator=(TimeRangeResult&&) noexcept = default;
    
            friend std::ostream& operator<<(std::ostream& os, const TimeRangeResult& obj);

            TimeRange getTimeRange();
            int getMarketCount();

        private:
            TimeRange time_range_;
            int market_count_;
        };
}