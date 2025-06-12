#pragma once

namespace BetfairAPI::BettingEnums {
    
    enum class OrderType {
        LIMIT, //A normal exchange limit order for immediate execution
        LIMIT_ON_CLOSE, //Limit order for the auction (SP)
        MARKET_ON_CLOSE, //Market order for the auction (SP)
    };
}