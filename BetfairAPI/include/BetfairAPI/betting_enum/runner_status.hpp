#pragma once

namespace BetfairAPI::BettingEnum {
    enum class RunnerStatus {
        ACTIVE,
        WINNER,
        LOSER,
        PLACED,
        REMOVED_VACANT,
        REMOVED,
        HIDDEN,
    };
}