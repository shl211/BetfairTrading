#include "event_result.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    EventResult::EventResult(Event event,int market_count) 
        : event_(std::move(event)), market_count_(market_count) {}


    std::ostream& operator<<(std::ostream& os, const EventResult& result) {
        os << "Event: " << result.event_ << ", Market Count: " << result.market_count_;
        return os;
    }


    Event EventResult::getEvent() {
        return event_;
    }

    int EventResult::getMarketCount() {
        return market_count_;
    }
}