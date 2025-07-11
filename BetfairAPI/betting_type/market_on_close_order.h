#pragma once

namespace BetfairAPI::BettingType {
    class MarketOnCloseOrder {
        public:
            explicit MarketOnCloseOrder(double liability);
            ~MarketOnCloseOrder() = default;
            MarketOnCloseOrder() = default;
            MarketOnCloseOrder(const MarketOnCloseOrder&) = default;
            MarketOnCloseOrder(MarketOnCloseOrder&&) noexcept = default;
            MarketOnCloseOrder& operator=(const MarketOnCloseOrder&) = default;
            MarketOnCloseOrder& operator=(MarketOnCloseOrder&&) noexcept = default;
        
            bool operator==(const MarketOnCloseOrder& other) const;
            bool operator!=(const MarketOnCloseOrder& other) const;

            double getLiability() const;

        private:
            double liability_;
    };
}