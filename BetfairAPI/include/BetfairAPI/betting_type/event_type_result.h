#pragma once

#include "BetfairAPI/betting_type/event_type.h"
#include <ostream>

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

    inline std::ostream& operator<<(std::ostream& os,const EventTypeResult& et_res) {
        os << "Event type result: " << et_res.eventType << " with market count " << et_res.marketCount;
        return os;
    }
}