#include "market_type_result.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    MarketTypeResult::MarketTypeResult(std::string_view market_type, int market_count) 
        : market_type_(market_type), market_count_(market_count) {}

    std::ostream& operator<<(std::ostream& os, const MarketTypeResult& obj) {
        os << "MarketTypeResult{market_type=" << obj.getMarketType()
        << ", market_count=" << obj.getMarketCount() << "}";
        return os;
    }

    std::string MarketTypeResult::getMarketType() const {
        return market_type_;
    }

    int MarketTypeResult::getMarketCount() const {
        return market_count_;
    }

}