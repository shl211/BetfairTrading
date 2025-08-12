#pragma once

#include <string>
#include <optional>
#include <memory>
#include <ostream>
#include "BetfairAPI/streaming_type/runner_change.h"
#include "BetfairAPI/streaming_type/market_description.h"

namespace BetfairAPI::StreamingType {
    struct MarketChange {
        std::string marketId;//id
        double tradedVolume;//tv
        std::optional<bool> image;//img
        std::unique_ptr<MarketDefinition> marketDefinition;
        std::vector<RunnerChange> runnerChange;
    };

    inline bool operator==(const MarketChange& lhs, const MarketChange& rhs) {
        return lhs.marketId == rhs.marketId &&
               lhs.tradedVolume == rhs.tradedVolume &&
               lhs.image == rhs.image &&
               ((!lhs.marketDefinition && !rhs.marketDefinition) ||
                (lhs.marketDefinition && rhs.marketDefinition &&
                 *lhs.marketDefinition == *rhs.marketDefinition)) &&
               lhs.runnerChange == rhs.runnerChange;
    }

    inline bool operator!=(const MarketChange& lhs, const MarketChange& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketChange& mc) {
        os << "MarketChange(marketId: " << mc.marketId
           << ", tradedVolume: " << mc.tradedVolume
           << ", image: " << (mc.image ? *mc.image : false)
           << ", marketDefinition: ";
        if (mc.marketDefinition) {
            os << *mc.marketDefinition;
        } else {
            os << "null";
        }
        os << ", runnerChange: [";
        for (size_t i = 0; i < mc.runnerChange.size(); ++i) {
            os << mc.runnerChange[i];
            if (i != mc.runnerChange.size() - 1) {
            os << ", ";
            }
        }
        os << "])";
        return os;
    }
}