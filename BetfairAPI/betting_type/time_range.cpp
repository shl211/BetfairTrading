#include "time_range.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    TimeRange::TimeRange(BetfairAPI::Utils::Date from,BetfairAPI::Utils::Date to) 
        : from_date_(std::move(from)), to_date_(std::move(to)) {}

    bool TimeRange::operator==(const TimeRange& other) const {
        return from_date_ == other.from_date_ && to_date_ == other.to_date_;
    }

    bool TimeRange::operator!=(const TimeRange& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const TimeRange& timeRange) {
        os << "TimeRange(from: " << timeRange.from_date_ << ", to: " << timeRange.to_date_ << ")";
        return os;
    }

    BetfairAPI::Utils::Date TimeRange::getFromDate() const {
        return from_date_;
    }

    BetfairAPI::Utils::Date TimeRange::getToDate() const {
        return to_date_;
    }
}
