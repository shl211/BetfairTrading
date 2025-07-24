#pragma once

#include <optional>
#include <string>
#include "BetfairAPI/date.h"
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_enum/market_betting_type.hpp"
#include "BetfairAPI/betting_type/market_line_range_info.h"
#include "BetfairAPI/betting_type/price_ladder_description.h"

namespace BetfairAPI::BettingType {
    struct MarketDescription {
        bool persistenceEnabled;
        bool bspMarket;
        std::optional<Date> marketTime;
        std::optional<Date> suspendTime;
        std::optional<Date> settleTime;
        BettingEnum::MarketBettingType bettingType;
        bool turnInPlay;
        std::string marketType;
        std::string regulator;
        double marketBaseRate;
        bool discountAllowed;
        
        //optioanl
        std::string wallet = "";
        std::string rules = "";
        std::optional<bool> rulesHasDate;
        double eachWayDivisor = 0.0;
        std::string clarifications;
        std::optional<MarketLineRangeInfo> lineRangeInfo;
        std::string raceType = "";
        std::optional<PriceLadderDescription> priceLadderDescription;
    };

    inline bool operator==(const MarketDescription& lhs, const MarketDescription& rhs) {
        return lhs.persistenceEnabled == rhs.persistenceEnabled &&
                lhs.bspMarket == rhs.bspMarket &&
                lhs.marketTime == rhs.marketTime &&
                lhs.suspendTime == rhs.suspendTime &&
                lhs.settleTime == rhs.settleTime &&
                lhs.bettingType == rhs.bettingType &&
                lhs.turnInPlay == rhs.turnInPlay &&
                lhs.marketType == rhs.marketType &&
                lhs.regulator == rhs.regulator &&
                lhs.marketBaseRate == rhs.marketBaseRate &&
                lhs.discountAllowed == rhs.discountAllowed &&
                lhs.wallet == rhs.wallet &&
                lhs.rules == rhs.rules &&
                lhs.rulesHasDate == rhs.rulesHasDate &&
                lhs.eachWayDivisor == rhs.eachWayDivisor &&
                lhs.clarifications == rhs.clarifications &&
                lhs.lineRangeInfo == rhs.lineRangeInfo &&
                lhs.raceType == rhs.raceType &&
                lhs.priceLadderDescription == rhs.priceLadderDescription;
    }

    inline bool operator!=(const MarketDescription& lhs, const MarketDescription& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketDescription& md) {
        os << "MarketDescription{"
            << "persistenceEnabled=" << md.persistenceEnabled << ", "
            << "bspMarket=" << md.bspMarket << ", "
            << "marketTime=" <<((md.marketTime) ? md.marketTime->getIsoString() : "N/A") << ", "
            << "suspendTime=" << ((md.suspendTime) ? md.suspendTime->getIsoString() : "N/A") << ", "
            << "settleTime=";
        if (md.settleTime) os << md.settleTime->getIsoString(); else os << "nullopt";
        os << ", bettingType=" << to_string(md.bettingType) //replace at some point with string
            << ", turnInPlay=" << md.turnInPlay 
            << ", marketType=" << md.marketType
            << ", regulator=" << md.regulator
            << ", marketBaseRate=" << md.marketBaseRate
            << ", discountAllowed=" << md.discountAllowed
            << ", wallet=" << md.wallet
            << ", rules=" << md.rules
            << ", rulesHasDate=";
        if (md.rulesHasDate) os << *md.rulesHasDate; else os << "nullopt";
        os << ", eachWayDivisor=" << md.eachWayDivisor
            << ", clarifications=" << md.clarifications
            << ", lineRangeInfo=";
        if (md.lineRangeInfo) os << *md.lineRangeInfo; else os << "nullopt";
        os << ", raceType=" << md.raceType
            << ", priceLadderDescription=";
        if (md.priceLadderDescription) os << *md.priceLadderDescription; else os << "nullopt";
        os << "}";
        return os;
    }


}