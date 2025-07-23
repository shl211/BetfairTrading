#pragma once

#include <vector>
#include <ostream>
#include "price_size.h"

namespace BetfairAPI::BettingType {
    struct ExchangePrices {
        std::vector<PriceSize> availableToBack;
        std::vector<PriceSize> availableToLay;
        std::vector<PriceSize> tradedVolume;
    };

    inline bool operator==(const ExchangePrices& lhs, const ExchangePrices& rhs) {
        return lhs.availableToBack == rhs.availableToBack &&
                lhs.availableToLay == rhs.availableToLay &&
                lhs.tradedVolume == rhs.tradedVolume;
    }

    inline bool operator!=(const ExchangePrices& lhs, const ExchangePrices& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ExchangePrices& ep) {
        os << "ExchangePrices{availableToBack=[";
        for (size_t i = 0; i < ep.availableToBack.size(); ++i) {
            if (i > 0) os << ", ";
            os << ep.availableToBack[i];
        }
        os << "], availableToLay=[";
        for (size_t i = 0; i < ep.availableToLay.size(); ++i) {
            if (i > 0) os << ", ";
            os << ep.availableToLay[i];
        }
        os << "], tradedVolume=[";
        for (size_t i = 0; i < ep.tradedVolume.size(); ++i) {
            if (i > 0) os << ", ";
            os << ep.tradedVolume[i];
        }
        os << "]}";
        return os;
    }
}