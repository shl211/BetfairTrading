#pragma once

namespace BetfairAPI::BettingEnums {
    enum class OrderProjection {
        ALL, //EXECUTABLE and EXECUTION_COMPLETE orders
        EXECUTABLE, //An order that has a remaining unmatched portion. This is either a fully unmatched or partially matched bet (order)
        EXECUTION_COMPLETE, //An order that does not have any remaining unmatched portion.  This is a fully matched bet (order).
    };
}