#pragma once

//this is for legacy data

namespace BetfairAPI::BettingEnum {
    enum class MarketType {
        A,//Asian Handicap
        L,//Line market
        O,//Odds market
        R,//Range market.
        NOT_APPLICABLE,//The market does not have an applicable marketType.
    };
}