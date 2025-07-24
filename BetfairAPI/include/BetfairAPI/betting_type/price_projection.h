#pragma once

#include <set>
#include <optional>
#include <ostream>

#include "BetfairAPI/betting_enum/price_data.hpp"
#include "BetfairAPI/utils.h"
#include "BetfairAPI/betting_type/offers_overrides.h"

namespace BetfairAPI::BettingType {
    struct PriceProjection {
        std::set<BettingEnum::PriceData> priceData;
        std::optional<ExBestOffersOverrides> exBestOffersOverrides;
        std::optional<bool> virtualise;
        std::optional<bool> rolloverStakes;
    };

    inline bool operator==(const PriceProjection& lhs, const PriceProjection& rhs) {
        return lhs.priceData == rhs.priceData &&
                lhs.exBestOffersOverrides == rhs.exBestOffersOverrides &&
                lhs.virtualise == rhs.virtualise &&
                lhs.rolloverStakes == rhs.rolloverStakes;
    }

    inline bool operator!=(const PriceProjection& lhs, const PriceProjection& rhs) {
        return !(lhs == rhs);
    }

    #include <ostream>
    inline std::ostream& operator<<(std::ostream& os, const PriceProjection& pp) {
        os << "PriceProjection{priceData=[";
        for (auto it = pp.priceData.begin(); it != pp.priceData.end(); ++it) {
            if (it != pp.priceData.begin()) os << ", ";
            os << to_string(*it);
        }
        os << "]";
        if (pp.exBestOffersOverrides) {
            os << ", ExBestOffersOverrides=" << *pp.exBestOffersOverrides;
        } else {
            os << ", ExBestOffersOverrides=nullopt";
        }
        os << ", virtualise=" << (pp.virtualise ? (*pp.virtualise ? "true" : "false") : "nullopt");
        os << ", rolloverStakes=" << (pp.rolloverStakes ? (*pp.rolloverStakes ? "true" : "false") : "nullopt");
        os << "}";
        return os;
    }
}