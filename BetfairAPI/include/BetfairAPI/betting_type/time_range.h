#pragma once

#include <optional>
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

}