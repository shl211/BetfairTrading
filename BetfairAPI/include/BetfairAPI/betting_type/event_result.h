#pragma once

#include "BetfairAPI/betting_type/event.h"

namespace BetfairAPI::BettingType {
    struct EventResult {
        Event event;
        int marketCount = 0;
    };

    inline bool operator==(const EventResult& lhs, const EventResult& rhs) {
        return lhs.event == rhs.event && lhs.marketCount == rhs.marketCount;
    }

    inline bool operator!=(const EventResult& lhs, const EventResult& rhs) {
        return !(lhs == rhs);
    }

    inline std::ostream& operator<<(std::ostream& os, const EventResult& er) {
        return os << "EventResult{ event: " << er.event << ", marketCount: " << er.marketCount << " }";
    }
}