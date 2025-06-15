#include "time_range.h"

namespace BetfairAPI::BettingType {
    TimeRange::TimeRange(BetfairAPI::Utils::Date from,BetfairAPI::Utils::Date to) 
        : from_date_(std::move(from)), to_date_(std::move(to)) {}

    bool TimeRange::operator==(const TimeRange& other) const {
        return from_date_ == other.from_date_ && to_date_ == other.to_date_;
    }

    bool TimeRange::operator!=(const TimeRange& other) const {
        return !(*this == other);
    }

    BetfairAPI::Utils::Date TimeRange::getFromDate() const {
        return from_date_;
    }

    BetfairAPI::Utils::Date TimeRange::getToDate() const {
        return to_date_;
    }
}
