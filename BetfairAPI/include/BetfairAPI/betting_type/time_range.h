#pragma once

#include <optional>
#include "BetfairAPI/date.h"

namespace BetfairAPI::BettingType {
    struct TimeRange {
        std::optional<BetfairAPI::Date> from = std::nullopt;
        std::optional<BetfairAPI::Date> to = std::nullopt;
    };
}