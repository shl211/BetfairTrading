#include "event_type_results.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    EventTypeResults::EventTypeResults(EventType event_type, int market_count)
        : event_type_(std::move(event_type)), market_count_(market_count) {};

    std::ostream& operator<<(std::ostream& os, const EventTypeResults& obj) {
        os << "EventType: " << obj.event_type_ << ", MarketCount: " << obj.market_count_;
        return os;
    }

    int EventTypeResults::getMarketCount() const {
        return market_count_;
    }

    EventType EventTypeResults::getEventType() const {
        return event_type_;
    }
}