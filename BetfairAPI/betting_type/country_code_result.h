#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class CountryCodeResult {
        public:
            CountryCodeResult(const std::string& country_code,int market_count);
            CountryCodeResult() = default;
            ~CountryCodeResult() = default;
            CountryCodeResult(const CountryCodeResult&) = default;
            CountryCodeResult(CountryCodeResult&&) noexcept = default;
            CountryCodeResult& operator=(const CountryCodeResult&) = default;
            CountryCodeResult& operator=(CountryCodeResult&&) noexcept = default;
            
            friend std::ostream& operator<<(std::ostream& os, const CountryCodeResult& result);

            const std::string& getCountryCode() const;
            int getMarketCount() const;
        
            private:
            std::string country_code_;
            int market_count_;
    };
}