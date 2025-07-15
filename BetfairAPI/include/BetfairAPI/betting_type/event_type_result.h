#pragma once

#include "event_type.h"

namespace BetfairAPI::BettingType {
    struct EventTypeResult {
        EventType eventType;
        int marketCount = 0;
    };
}