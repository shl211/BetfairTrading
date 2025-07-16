#pragma once

#include <optional>
#include <ostream>
#include "BetfairAPI/date.h"

namespace BetfairAPI::BettingType {
    struct TimeRange {
        std::optional<BetfairAPI::Date> from = std::nullopt;
        std::optional<BetfairAPI::Date> to = std::nullopt;
    };

    inline bool operator==(const TimeRange& lhs, const TimeRange& rhs) {
        return lhs.from == rhs.from && lhs.to == rhs.to;
    }

    inline bool operator!=(const TimeRange& lhs, const TimeRange& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os,const TimeRange& tr) {
        os << "Time range " << 
            (tr.from ? tr.from->getIsoString() : "N/A") << " - " <<
            (tr.to ? tr.to->getIsoString() : "N/A") << " - ";

        return os;
    }
}