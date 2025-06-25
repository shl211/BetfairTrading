#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class MarketTypeResult {
        public:
            MarketTypeResult(std::string_view market_type, int market_count);
            MarketTypeResult() = default;
            ~MarketTypeResult() = default;
            MarketTypeResult(const MarketTypeResult& other) = default;
            MarketTypeResult(MarketTypeResult&& other) noexcept = default;
            MarketTypeResult& operator=(const MarketTypeResult& other) = default;
            MarketTypeResult& operator=(MarketTypeResult&& other) noexcept = default;

            friend std::ostream& operator<<(std::ostream& os, const MarketTypeResult& obj);

            std::string getMarketType() const;
            int getMarketCount() const;

        private:
            std::string market_type_;
            int market_count_;
    };
}