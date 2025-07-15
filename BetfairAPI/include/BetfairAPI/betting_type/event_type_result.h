#pragma once

#include "event_type.h"

namespace BetfairAPI::BettingType {
    struct EventTypeResult {
        EventType eventType;
        int marketCount = 0;
    };

    inline bool operator==(const EventTypeResult& lhs,const EventTypeResult& rhs) {
        return lhs.eventType == rhs.eventType && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const EventTypeResult& lhs,const EventTypeResult& rhs) {
        return !(lhs==rhs);
    }
}