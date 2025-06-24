#pragma once

#include "utils/date_utils.h"

namespace BetfairAPI::BettingType {
    class TimeRange {
        public:
            TimeRange(BetfairAPI::Utils::Date from,BetfairAPI::Utils::Date to);
            TimeRange() = default;
            ~TimeRange() = default;
            TimeRange(const TimeRange&) = default;
            TimeRange(TimeRange&&) noexcept = default;
            TimeRange& operator=(const TimeRange&) = default;
            TimeRange& operator=(TimeRange&&) noexcept = default;
        
            bool operator==(const TimeRange& other) const;
            bool operator!=(const TimeRange& other) const;

            BetfairAPI::Utils::Date getFromDate() const;
            BetfairAPI::Utils::Date getToDate() const;

        private:
            BetfairAPI::Utils::Date from_date_;
            BetfairAPI::Utils::Date to_date_;
    };
}