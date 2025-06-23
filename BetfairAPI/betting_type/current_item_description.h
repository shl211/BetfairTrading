#pragma once
#include "market_version.h"

namespace BetfairAPI::BettingType {
    class CurrentItemDescription {
        public:
            CurrentItemDescription(MarketVersion v);
            CurrentItemDescription() = default;
            ~CurrentItemDescription() = default;
            CurrentItemDescription(const CurrentItemDescription&) = default;
            CurrentItemDescription(CurrentItemDescription&&) noexcept = default;
            CurrentItemDescription& operator=(const CurrentItemDescription&) = default;
            CurrentItemDescription& operator=(CurrentItemDescription&&) noexcept = default;
        
            MarketVersion getMarketVersion() const;

        private:
            MarketVersion market_version_;
    };
}