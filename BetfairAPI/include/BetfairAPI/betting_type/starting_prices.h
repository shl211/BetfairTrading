#pragma once

#include <optional>
#include <ostream>
#include <vector>
#include "BetfairAPI/betting_type/price_size.h"

namespace BetfairAPI::BettingType {
    struct StartingPrices {
        std::optional<double> nearPrice;
        std::optional<double> farPrice;
        std::vector<PriceSize> backStakeTaken;
        std::vector<PriceSize> layLiabilityTaken;
        std::optional<double> actualSP;
    };

    inline bool operator==(const StartingPrices& lhs, const StartingPrices& rhs) {
        return lhs.nearPrice == rhs.nearPrice &&
               lhs.farPrice == rhs.farPrice &&
               lhs.backStakeTaken == rhs.backStakeTaken &&
               lhs.layLiabilityTaken == rhs.layLiabilityTaken &&
               lhs.actualSP == rhs.actualSP;
    }

    inline bool operator!=(const StartingPrices& lhs, const StartingPrices& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const StartingPrices& sp) {
        os << "StartingPrices{";
        os << "nearPrice=";
        if (sp.nearPrice) os << *sp.nearPrice; else os << "null";
        os << ", farPrice=";
        if (sp.farPrice) os << *sp.farPrice; else os << "null";
        os << ", backStakeTaken=[";
        for (size_t i = 0; i < sp.backStakeTaken.size(); ++i) {
            if (i > 0) os << ", ";
            os << sp.backStakeTaken[i];
        }
        os << "], layLiabilityTaken=[";
        for (size_t i = 0; i < sp.layLiabilityTaken.size(); ++i) {
            if (i > 0) os << ", ";
            os << sp.layLiabilityTaken[i];
        }
        os << "], actualSP=";
        if (sp.actualSP) os << *sp.actualSP; else os << "null";
        os << "}";
        return os;
    }
}