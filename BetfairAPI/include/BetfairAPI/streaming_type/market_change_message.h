#pragma once

#include <string>
#include <memory>
#include <vector>
#include <ostream>
#include "BetfairAPI/streaming_type/change_message.h"
#include "BetfairAPI/streaming_type/market_change.h"

namespace BetfairAPI::StreamingType {
    struct MarketChangeMessage : public ChangeMessage {
        std::vector<MarketChange> marketChange;
    };

    inline bool operator==(const MarketChangeMessage& lhs, const MarketChangeMessage& rhs) {
        return static_cast<const ChangeMessage&>(lhs) == static_cast<const ChangeMessage&>(rhs) &&
               lhs.marketChange == rhs.marketChange;
    }

    inline bool operator!=(const MarketChangeMessage& lhs, const MarketChangeMessage& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketChangeMessage& obj) {
        os << static_cast<const ChangeMessage&>(obj);
        os << " MarketChange: [";
        for (const auto& market : obj.marketChange) {
            os << market << ", ";
        }
        os << "]";
        return os;
    }
}