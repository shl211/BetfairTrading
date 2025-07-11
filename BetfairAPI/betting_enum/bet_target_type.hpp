#pragma once

namespace BetfairAPI::BettingEnum {
    enum class BetTargetType {
        BACKERS_PROFIT,//The payout requested minus the calculated size at which this LimitOrder is to be placed. BetTargetType bets are invalid for LINE markets
        PAYOUT,//The total payout requested on a LimitOrder
    };
}