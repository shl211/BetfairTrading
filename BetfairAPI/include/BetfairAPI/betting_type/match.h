#pragma once

#include <optional> 
#include <string> 
#include <ostream> 
#include "BetfairAPI/betting_enum/side.hpp"
#include "BetfairAPI/date.h"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::BettingType {
    struct Match {
        std::optional<std::string> betId;
        std::optional<std::string> matchId;
        BettingEnum::Side side;
        double price;
        double size;
        std::optional<Date> matchDate;
    };

    inline bool operator==(const Match& lhs, const Match& rhs) {
        return lhs.betId == rhs.betId &&
               lhs.matchId == rhs.matchId &&
               lhs.side == rhs.side &&
               lhs.price == rhs.price &&
               lhs.size == rhs.size &&
               lhs.matchDate == rhs.matchDate;
    }

    inline bool operator!=(const Match& lhs, const Match& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const Match& match) {
        os << "Match{"
           << "betId=" << (match.betId ? *match.betId : "null") << ", "
           << "matchId=" << (match.matchId ? *match.matchId : "null") << ", "
           << "side=" << to_string(match.side) << ", "
           << "price=" << match.price << ", "
           << "size=" << match.size << ", "
           << "matchDate=";
        if (match.matchDate) {
            os << match.matchDate->getIsoString();
        } else {
            os << "null";
        }
        os << "}";
        return os;
    }
}