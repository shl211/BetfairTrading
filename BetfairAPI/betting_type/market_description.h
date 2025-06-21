#pragma once

#include <string>

#include "utils/date_utils.h"
#include "betting_enum/market_betting_type.hpp"
#include "market_line_range_info.h"
#include "price_ladder_description.h"

namespace BetfairAPI::BettingType {
    class MarketDescription {
        public:
        MarketDescription() = default;
        ~MarketDescription() = default;
        MarketDescription(const MarketDescription&) = default;
        MarketDescription(MarketDescription&&) noexcept = default;
        MarketDescription& operator=(const MarketDescription&) = default;
        MarketDescription& operator=(MarketDescription&&) noexcept = default;

        // Getters
        bool isPersistenceEnabled() const;
        bool isBspMarket() const;
        const BetfairAPI::Utils::Date& getMarketTime() const;
        const BetfairAPI::Utils::Date& getSuspendTime() const;
        const BetfairAPI::Utils::Date& getSettleTime() const;
        BetfairAPI::BettingEnum::MarketBettingType getBettingType() const;
        bool isTurnInPlayEnabled() const;
        const std::string& getMarketType() const;
        const std::string& getRegulator() const;
        double getMarketBaseRate() const;
        bool isDiscountAllowed() const;
        const std::string& getWallet() const;
        const std::string& getRules() const;
        bool hasRulesWithDates() const;
        double getEachWayDivisor() const;
        const std::string& getClarifications() const;
        const MarketLineRangeInfo& getLineRangeInfo() const;
        const std::string& getRaceType() const;
        const PriceLadderDescription& getPriceLadderDescription() const;

        // Setters
        void setPersistenceEnabled(bool value);
        void setBspMarket(bool value);
        void setMarketTime(const BetfairAPI::Utils::Date& value);
        void setSuspendTime(const BetfairAPI::Utils::Date& value);
        void setSettleTime(const BetfairAPI::Utils::Date& value);
        void setBettingType(BetfairAPI::BettingEnum::MarketBettingType value);
        void setTurnInPlayEnabled(bool value);
        void setMarketType(const std::string& value);
        void setRegulator(const std::string& value);
        void setMarketBaseRate(double value);
        void setDiscountAllowed(bool value);
        void setWallet(const std::string& value);
        void setRules(const std::string& value);
        void setRulesHasDates(bool value);
        void setEachWayDivisor(double value);
        void setClarifications(const std::string& value);
        void setLineRangeInfo(const MarketLineRangeInfo& value);
        void setRaceType(const std::string& value);
        void setPriceLadderDescription(const PriceLadderDescription& value);

        private:
            bool persistence_enabled_;
            bool bsp_market_;
            BetfairAPI::Utils::Date market_time_;
            BetfairAPI::Utils::Date suspend_time_;
            BetfairAPI::Utils::Date settle_time_;
            BetfairAPI::BettingEnum::MarketBettingType betting_type_;
            bool turn_in_play_enabled_;
            std::string market_type_;
            std::string regulator_;
            double market_base_rate_;
            bool discount_allowed_;
            std::string wallet_;
            std::string rules_;
            bool rules_has_dates_;
            double each_way_divisor_;
            std::string clarifications_;
            MarketLineRangeInfo line_range_info_;
            std::string race_type_;
            PriceLadderDescription price_ladder_description_;

    };
}