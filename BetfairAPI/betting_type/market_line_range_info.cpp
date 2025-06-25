#include "market_line_range_info.h"

namespace BetfairAPI::BettingType {

    MarketLineRangeInfo::MarketLineRangeInfo(double max_unit_value, double min_unit_value,
                                            double interval, std::string_view market_unit)
        : max_unit_value_(max_unit_value),
        min_unit_value_(min_unit_value),
        interval_(interval),
        market_unit_(market_unit) {}

    bool MarketLineRangeInfo::operator==(const MarketLineRangeInfo& other) const {
        return max_unit_value_ == other.max_unit_value_ &&
            min_unit_value_ == other.min_unit_value_ &&
            interval_ == other.interval_ &&
            market_unit_ == other.market_unit_;
    }

    bool MarketLineRangeInfo::operator!=(const MarketLineRangeInfo& other) const {
        return !(*this == other);
    }


    double MarketLineRangeInfo::getMaxUnitValue() const {
        return max_unit_value_;
    }

    double MarketLineRangeInfo::getMinUnitValue() const {
        return min_unit_value_;
    }

    double MarketLineRangeInfo::getInterval() const {
        return interval_;
    }

    const std::string& MarketLineRangeInfo::getMarketUnit() const {
        return market_unit_;
    }
}