#include "country_code_result.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    CountryCodeResult::CountryCodeResult(const std::string& country_code,int market_count)
        : country_code_(country_code), market_count_(market_count) {}


    std::ostream& operator<<(std::ostream& os, const CountryCodeResult& result) {
        os << "CountryCodeResult{country_code=" << result.country_code_
            << ", market_count=" << result.market_count_ << "}";
        return os;
    }

    const std::string& CountryCodeResult::getCountryCode() const {
        return country_code_;
    }

    int CountryCodeResult::getMarketCount() const {
        return market_count_;
    }
}