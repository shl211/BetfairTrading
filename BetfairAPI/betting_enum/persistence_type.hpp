#pragma once

namespace BetfairAPI::BettingEnum {
    enum class PersistenceType {
        LAPSE,//Lapse (cancel) the order automatically when the market is turned in play if the bet is unmatched
        PERSIST,//Persist the unmatched order to in-play. The bet will be placed automatically into the in-play market at the start of the event. 
        MARKET_ON_CLOSE,//Put the order into the auction (SP) at turn-in-play
    };
}