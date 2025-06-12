#pragma once

#include "EventType.h"

namespace BetfairAPI::BettingType {
    class EventTypeResults {
        public:
            EventTypeResults(EventType event_type_, int market_count);
            ~EventTypeResults()=default;

            int getMarketCount() const;
            EventType getEventType() const;

        private:
            EventType event_type_;
            int market_count_;
    };
}