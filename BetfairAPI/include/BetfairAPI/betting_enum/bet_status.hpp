#pragma once

namespace BetfairAPI::BettingEnum {
    enum class BetStatus {
        SETTLED,
        VOIDED,
        LAPSED,
        CANCELLED,
    };
}