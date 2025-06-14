#include "event_result.h"

namespace BetfairAPI::BettingType {
    EventResult::EventResult(Event event,int market_count) 
        : event_(std::move(event)), market_count_(market_count) {}

    Event EventResult::getEvent() {
        return event_;
    }

    int EventResult::getMarketCount() {
        return market_count_;
    }
}