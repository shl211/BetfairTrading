#pragma once

#include "event_type.h"

namespace BetfairAPI::BettingType {
    class EventTypeResults {
        public:
            EventTypeResults(EventType event_type_, int market_count);
            ~EventTypeResults()=default;
            EventTypeResults(const EventTypeResults&) = default;
            EventTypeResults(EventTypeResults&&) noexcept = default;
            EventTypeResults& operator=(const EventTypeResults&) = default;
            EventTypeResults& operator=(EventTypeResults&&) noexcept = default;

            int getMarketCount() const;
            EventType getEventType() const;

        private:
            EventType event_type_;
            int market_count_;
    };
}