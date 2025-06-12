#pragma once

#include "EventType.h"

namespace BetfairAPI::BettingType {
    class EventTypeResults {
        public:
            EventTypeResults(EventType event_type_, int market_count);
            ~EventTypeResults()=default;
            //compiler defaults for copy and move semantics should be ok
            //as members also have those semantics implemented

            int getMarketCount() const;
            EventType getEventType() const;

        private:
            EventType event_type_;
            int market_count_;
    };
}