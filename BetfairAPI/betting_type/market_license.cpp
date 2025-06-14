#include "market_license.h"

namespace BetfairAPI::BettingType {
    MarketLicense::MarketLicense(std::string_view wallet,std::string_view rules,bool rules_has_date,std::string_view clarifications) 
        : wallet_(wallet), rules_(rules), rules_has_date_(rules_has_date), clarifications_(clarifications) {}

    std::string MarketLicense::getWallet() const {
        return wallet_;
    }

    std::string MarketLicense::getRules() const {
        return rules_;
    }

    bool MarketLicense::isRulesHasDate() const {
        return rules_has_date_;
    }

    std::string MarketLicense::getClarifications() const {
        return clarifications_;
    }
}