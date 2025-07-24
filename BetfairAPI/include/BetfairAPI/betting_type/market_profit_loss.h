#pragma once

#include <ostream>
#include <optional>
#include <string>
#include <vector>
#include "BetfairAPI/betting_type/runner_profit_loss.h"

namespace BetfairAPI::BettingType {
    struct MarketProfitAndLoss {
        std::string marketId;
        std::optional<double> commissionApplied;
        std::vector<RunnerProfitAndLoss> profitAndLoss;
    };

    inline bool operator==(const MarketProfitAndLoss& lhs, const MarketProfitAndLoss& rhs) {
        return lhs.marketId == rhs.marketId &&
                lhs.commissionApplied == rhs.commissionApplied &&
                lhs.profitAndLoss == rhs.profitAndLoss;
    }

    inline bool operator!=(const MarketProfitAndLoss& lhs, const MarketProfitAndLoss& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketProfitAndLoss& obj) {
        os << "MarketProfitAndLoss{marketId=" << obj.marketId
            << ", commissionApplied=";
        if (obj.commissionApplied)
            os << *obj.commissionApplied;
        else
            os << "nullopt";
        os << ", profitAndLoss=[";
        for (size_t i = 0; i < obj.profitAndLoss.size(); ++i) {
            os << obj.profitAndLoss[i];
            if (i + 1 < obj.profitAndLoss.size())
                os << ", ";
        }
        os << "]}";
        return os;
    }
}