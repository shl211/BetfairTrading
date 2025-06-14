#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class MarketLicense {
        public:
            MarketLicense(std::string_view wallet,std::string_view rules,bool rules_has_date,std::string_view clarifications);
            ~MarketLicense() = default;
            MarketLicense(const MarketLicense&) = default;
            MarketLicense(MarketLicense&&) noexcept = default;
            MarketLicense& operator=(const MarketLicense&) = default;
            MarketLicense& operator=(MarketLicense&&) noexcept = default;

            std::string getWallet() const;
            std::string getRules() const;
            bool isRulesHasDate() const;
            std::string getClarifications() const;

        private:
            std::string wallet_;
            std::string rules_;
            bool rules_has_date_;
            std::string clarifications_;
    };
}