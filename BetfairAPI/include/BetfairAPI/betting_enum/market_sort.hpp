#pragma once

namespace BetfairAPI::BettingEnum {
    enum class MarketSort {
        MINIMUM_TRADED,
        MAXIMUM_TRADED,
        MINIMUM_AVAILABLE,
        MAXIMUM_AVAILABLE,
        FIRST_TO_START,
        LAST_TO_START
    };
}