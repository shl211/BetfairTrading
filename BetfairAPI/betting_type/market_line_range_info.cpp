#include "market_line_range_info.h"

namespace BetfairAPI::BettingType {

    MarketLineRangeInfo::MarketLineRangeInfo(double max_unit_value, double min_unit_value,
                                            double interval, std::string_view market_unit)
        : max_unit_value_(max_unit_value),
        min_unit_value_(min_unit_value),
        interval_(interval),
        market_unit_(market_unit) {}

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