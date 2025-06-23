#include "country_code_result.h"

namespace BetfairAPI::BettingType {
    CountryCodeResult::CountryCodeResult(const std::string& country_code,int market_count)
        : country_code_(country_code), market_count_(market_count) {}
    
    const std::string& CountryCodeResult::getCountryCode() const {
        return country_code_;
    }

    int CountryCodeResult::getMarketCount() const {
        return market_count_;
    }
}