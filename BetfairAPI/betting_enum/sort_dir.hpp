#pragma once

namespace BetfairAPI::BettingEnum {
    enum class SortDir {
        UNKNOWN,
        EARLIEST_TO_LATEST,//Order from earliest value to latest e.g. lowest betId is first in the results.
        LATEST_TO_EARLIEST,//Order from the latest value to the earliest e.g. highest betId is first in the results.
    };
}