#pragma once

namespace BetfairAPI::BettingType {
    class MarketRates {
        public:
            MarketRates(double market_base_rate, bool discount_allowed);
            ~MarketRates() = default;
            MarketRates(const MarketRates&) = default;
            MarketRates(MarketRates&&) noexcept = default;
            MarketRates& operator=(const MarketRates&) = default;
            MarketRates& operator=(MarketRates&&) noexcept = default;

            double getMarketBaseRate() const;
            bool isDiscountAllowed() const;

        private:
            double market_base_rate_;
            bool discount_allowed_;
    };
}