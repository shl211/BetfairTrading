#pragma once

#include <memory>
#include "BetfairAPI/streaming_type/change_message.h"
#include "BetfairAPI/streaming_type/runner_change.h"
#include "BetfairAPI/streaming_type/market_description.h"

namespace BetfairAPI::StreamingType {
    struct MarketChangeMessage : public ChangeMessage {
        std::unique_ptr<MarketDefinition> marketDefinition;
        double totalValueMatched;
        bool replaceImage;//if true -> received new image, if false -> received deltas
        RunnerChange runnerChange;
    };

    inline bool operator==(const MarketChangeMessage& lhs, const MarketChangeMessage& rhs) {
        // Compare base
        if (!(static_cast<const ChangeMessage&>(lhs) == static_cast<const ChangeMessage&>(rhs))) {
            return false;
        }

        // Compare unique_ptr<MarketDefinition> by value
        bool marketDefEqual =
            (!lhs.marketDefinition && !rhs.marketDefinition) || 
            (lhs.marketDefinition && rhs.marketDefinition && *lhs.marketDefinition == *rhs.marketDefinition);

        return marketDefEqual
            && lhs.totalValueMatched == rhs.totalValueMatched
            && lhs.replaceImage == rhs.replaceImage
            && lhs.runnerChange == rhs.runnerChange;
    }

    inline bool operator!=(const MarketChangeMessage& lhs, const MarketChangeMessage& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const MarketChangeMessage& msg) {
        os << static_cast<const ChangeMessage&>(msg) << ", "; // print base
        os << "MarketChangeMessage{";
        os << "marketDefinition: " << (msg.marketDefinition ? *msg.marketDefinition : MarketDefinition{}) << ", ";
        os << "totalValueMatched: " << msg.totalValueMatched << ", ";
        os << "replaceImage: " << std::boolalpha << msg.replaceImage << ", ";
        os << "runnerChange: " << msg.runnerChange;
        os << "}";
        return os;
    }
}