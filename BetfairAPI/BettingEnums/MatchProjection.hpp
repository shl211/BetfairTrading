#pragma once

namespace BetfairAPI::BettingEnums {
    enum class MatchProjection {
        NO_ROLLUP, //No rollup, return raw fragments
        ROLLED_UP_BY_PRICE, //Rollup matched amounts by distinct matched prices per side.
        ROLLED_UP_BY_AVG_PRICE, //Rollup matched amounts by average matched price per side
    };
}