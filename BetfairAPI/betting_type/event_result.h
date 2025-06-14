#pragma once

#include "event.h"

namespace BetfairAPI::BettingType {
    class EventResult {
        public:
            EventResult(Event event, int market_count);
            ~EventResult() = default;
            EventResult(const EventResult&) = default;
            EventResult(EventResult&&) noexcept = default;
            EventResult& operator=(const EventResult&) = default;
            EventResult& operator=(EventResult&&) noexcept = default;

            Event getEvent();
            int getMarketCount();

        private:
            Event event_;
            int market_count_;
    };
}