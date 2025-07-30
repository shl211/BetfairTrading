#pragma once

#include <memory>
#include "BetfairAPI/streaming_type/change_message.h"
#include "BetfairAPI/streaming_type/market_description.h"

namespace BetfairAPI::StreamingType {
    struct MarketChangeMessage : public ChangeMessage {
        std::unique_ptr<MarketDefinition> marketDefinition;
        double totalValueMatched;
        bool replaceImage;//if true -> received new image, if false -> received deltas
    };
}