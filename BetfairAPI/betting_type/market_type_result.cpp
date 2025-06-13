#include "market_type_result.h"

namespace BetfairAPI::BettingType {
    MarketTypeResult::MarketTypeResult(std::string_view market_type, int market_count) 
        : market_type_(market_type), market_count_(market_count) {}

    std::string MarketTypeResult::getMarketType() const {
        return market_type_;
    }

    int MarketTypeResult::getMarketCount() const {
        return market_count_;
    }

}