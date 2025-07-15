#pragma once

namespace BetfairAPI::BettingEnum {
    enum class OrderStatus {
        PENDING,
        EXECUTION_COMPLETE,
        EXECUTABLE,
        EXPIRED,
    };
}
