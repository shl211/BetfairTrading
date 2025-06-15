#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class MarketLineRangeInfo {
        public:
            MarketLineRangeInfo(double max_unit_value, double min_unit_value,
                                double interval, std::string_view market_unit);
            ~MarketLineRangeInfo() = default;
            MarketLineRangeInfo(const MarketLineRangeInfo&) = default;
            MarketLineRangeInfo(MarketLineRangeInfo&&) noexcept = default;
            MarketLineRangeInfo& operator=(const MarketLineRangeInfo&) = default;
            MarketLineRangeInfo& operator=(MarketLineRangeInfo&&) noexcept = default;

            double getMaxUnitValue() const;
            double getMinUnitValue() const;
            double getInterval() const;
            const std::string& getMarketUnit() const;

        private:
            double max_unit_value_;
            double min_unit_value_;
            double interval_;
            std::string market_unit_;
    };
}