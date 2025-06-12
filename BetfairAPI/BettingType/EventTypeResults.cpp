#include "EventTypeResults.h"

namespace BetfairAPI::BettingType {
    EventTypeResults::EventTypeResults(EventType event_type, int market_count)
        : event_type_(event_type), market_count_(market_count) {};

    int EventTypeResults::getMarketCount() const {
        return market_count_;
    }

    EventType EventTypeResults::getEventType() const {
        return event_type_;
    }
}