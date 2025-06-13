#include "event_type_results.h"

namespace BetfairAPI::BettingType {
    EventTypeResults::EventTypeResults(EventType event_type, int market_count)
        : event_type_(std::move(event_type)), market_count_(market_count) {};

    int EventTypeResults::getMarketCount() const {
        return market_count_;
    }

    EventType EventTypeResults::getEventType() const {
        return event_type_;
    }
}