#pragma once 

#include <optional>
#include <ostream>
#include "BetfairAPI/betting_enum/rollup_model.hpp"
#include "BetfairAPI/utils.h"

namespace BetfairAPI::BettingType {
    struct ExBestOffersOverrides {
        std::optional<int> bestPricesDepth;
        std::optional<BettingEnum::RollupModel> rollupModel;
        std::optional<int> rollupLimit;
        std::optional<double> rollupLiabilityThreshold;
        std::optional<int> rollupLiabilityFactor;
    };

    inline bool operator==(const ExBestOffersOverrides& lhs, const ExBestOffersOverrides& rhs) {
        return lhs.bestPricesDepth == rhs.bestPricesDepth &&
                lhs.rollupModel == rhs.rollupModel &&
                lhs.rollupLimit == rhs.rollupLimit &&
                lhs.rollupLiabilityThreshold == rhs.rollupLiabilityThreshold &&
                lhs.rollupLiabilityFactor == rhs.rollupLiabilityFactor;
    }

    inline bool operator!=(const ExBestOffersOverrides& lhs, const ExBestOffersOverrides& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const ExBestOffersOverrides& obj) {
        os << "ExBestOffersOverrides{";
        os << "bestPricesDepth=" << (obj.bestPricesDepth ? std::to_string(*obj.bestPricesDepth) : "nullopt") << ", ";
        os << "rollupModel=";
        if (obj.rollupModel) {
            os << to_string(*obj.rollupModel);
        } else {
            os << "nullopt";
        }
        os << ", rollupLimit=" << (obj.rollupLimit ? std::to_string(*obj.rollupLimit) : "nullopt") << ", ";
        os << "rollupLiabilityThreshold=" << (obj.rollupLiabilityThreshold ? std::to_string(*obj.rollupLiabilityThreshold) : "nullopt") << ", ";
        os << "rollupLiabilityFactor=" << (obj.rollupLiabilityFactor ? std::to_string(*obj.rollupLiabilityFactor) : "nullopt");
        os << "}";
        return os;
    }
}