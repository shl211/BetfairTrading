#include "market_description.h"

namespace BetfairAPI::BettingType {
    // Getters
    bool MarketDescription::isPersistenceEnabled() const { 
        return persistence_enabled_; 
    }

    bool MarketDescription::isBspMarket() const { 
        return bsp_market_; 
    }

    const BetfairAPI::Utils::Date& MarketDescription::getMarketTime() const { 
        return market_time_; 
    }

    const BetfairAPI::Utils::Date& MarketDescription::getSuspendTime() const { 
        return suspend_time_; 
    }

    const BetfairAPI::Utils::Date& MarketDescription::getSettleTime() const { 
        return settle_time_; 
    }

    BetfairAPI::BettingEnum::MarketBettingType MarketDescription::getBettingType() const { 
        return betting_type_; 
    }

    bool MarketDescription::isTurnInPlayEnabled() const { 
        return turn_in_play_enabled_; 
    }

    const std::string& MarketDescription::getMarketType() const { 
        return market_type_; 
    }

    const std::string& MarketDescription::getRegulator() const { 
        return regulator_; 
    }

    double MarketDescription::getMarketBaseRate() const { 
        return market_base_rate_; 
    }

    bool MarketDescription::isDiscountAllowed() const { 
        return discount_allowed_; 
    }

    const std::string& MarketDescription::getWallet() const { 
        return wallet_; 
    }

    const std::string& MarketDescription::getRules() const { 
        return rules_; 
    }

    bool MarketDescription::hasRulesWithDates() const { 
        return rules_has_dates_; 
    }

    double MarketDescription::getEachWayDivisor() const { 
        return each_way_divisor_; 
    }

    const std::string& MarketDescription::getClarifications() const { 
        return clarifications_; 
    }

    const MarketLineRangeInfo& MarketDescription::getLineRangeInfo() const { 
        return line_range_info_; 
    }

    const std::string& MarketDescription::getRaceType() const { 
        return race_type_; 
    }

    const PriceLadderDescription& MarketDescription::getPriceLadderDescription() const { 
        return price_ladder_description_; 
    }

    // Setters
    void MarketDescription::setPersistenceEnabled(bool value) { 
        persistence_enabled_ = value; 
    }

    void MarketDescription::setBspMarket(bool value) { 
        bsp_market_ = value; 
    }

    void MarketDescription::setMarketTime(const BetfairAPI::Utils::Date& value) { 
        market_time_ = value; 
    }

    void MarketDescription::setSuspendTime(const BetfairAPI::Utils::Date& value) { 
        suspend_time_ = value; 
    }

    void MarketDescription::setSettleTime(const BetfairAPI::Utils::Date& value) { 
        settle_time_ = value; 
    }

    void MarketDescription::setBettingType(BetfairAPI::BettingEnum::MarketBettingType value) { 
        betting_type_ = value; 
    }

    void MarketDescription::setTurnInPlayEnabled(bool value) { 
        turn_in_play_enabled_ = value; 
    }

    void MarketDescription::setMarketType(const std::string& value) { 
        market_type_ = value; 
    }

    void MarketDescription::setRegulator(const std::string& value) { 
        regulator_ = value; 
    }

    void MarketDescription::setMarketBaseRate(double value) { 
        market_base_rate_ = value; 
    }

    void MarketDescription::setDiscountAllowed(bool value) { 
        discount_allowed_ = value; 
    }

    void MarketDescription::setWallet(const std::string& value) { 
        wallet_ = value; 
    }

    void MarketDescription::setRules(const std::string& value) { 
        rules_ = value; 
    }

    void MarketDescription::setRulesHasDates(bool value) { 
        rules_has_dates_ = value; 
    }

    void MarketDescription::setEachWayDivisor(double value) { 
        each_way_divisor_ = value; 
    }

    void MarketDescription::setClarifications(const std::string& value) { 
        clarifications_ = value; 
    }

    void MarketDescription::setLineRangeInfo(const MarketLineRangeInfo& value) { 
        line_range_info_ = value; 
    }

    void MarketDescription::setRaceType(const std::string& value) { 
        race_type_ = value; 
    }

    void MarketDescription::setPriceLadderDescription(const PriceLadderDescription& value) { 
        price_ladder_description_ = value; 
    }
}