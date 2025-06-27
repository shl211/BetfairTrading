#pragma once

#include <string>

#include "price_size.h"
#include "current_item_description.h"
#include "betting_enum/side.hpp"
#include "betting_enum/order_status.hpp"
#include "betting_enum/persistence_type.hpp"
#include "betting_enum/order_type.hpp"
#include "utils/date_utils.h"

namespace BetfairAPI::BettingType {
    class CurrentOrderSummary {
        public:
            CurrentOrderSummary(std::string_view bet_id,std::string_view market_id,long selection_id,
                double handicap,PriceSize price_size,double bsp_liability,BetfairAPI::BettingEnum::Side side,
                BetfairAPI::BettingEnum::OrderStatus status,BetfairAPI::BettingEnum::PersistenceType persistence_type,
                BetfairAPI::BettingEnum::OrderType order_type, BetfairAPI::Utils::Date placed_date,
                BetfairAPI::Utils::Date matched_date);
            CurrentOrderSummary() = default;
            ~CurrentOrderSummary() = default;
            CurrentOrderSummary(const CurrentOrderSummary&) = default;
            CurrentOrderSummary(CurrentOrderSummary&&) noexcept = default;
            CurrentOrderSummary& operator=(const CurrentOrderSummary&) = default;
            CurrentOrderSummary& operator=(CurrentOrderSummary&&) = default;

            friend std::ostream& operator<<(std::ostream& os, const CurrentOrderSummary& summary);

            void setAveragePriceMatched(double val);
            void setSizeMatched(double val);
            void setSizeRemaining(double val);
            void setSizeLapsed(double val);
            void setSizeCancelled(double val);
            void setSizeVoided(double val);
            void setRegulatorAuthCode(std::string_view s);
            void setRegulatorCode(std::string_view s);
            void setCustomerOrderRef(std::string_view s);
            void setCustomerStrategyRef(std::string_view s);
            void setCurrentItemDescription(CurrentItemDescription item);
            void setSourceIdKey(std::string_view s);
            void setSourceIdDescription(std::string_view s);

            const std::string& getBetId() const;
            const std::string& getMarketId() const;
            long getSelectionId() const;
            double getHandicap() const;
            const PriceSize& getPriceSize() const;
            double getBspLiability() const;
            BetfairAPI::BettingEnum::Side getSide() const;
            BetfairAPI::BettingEnum::OrderStatus getStatus() const;
            BetfairAPI::BettingEnum::PersistenceType getPersistenceType() const;
            BetfairAPI::BettingEnum::OrderType getOrderType() const;
            const BetfairAPI::Utils::Date& getPlacedDate() const;
            const BetfairAPI::Utils::Date& getMatchedDate() const;
            double getAveragePriceMatched() const;
            double getSizeMatched() const;
            double getSizeRemaining() const;
            double getSizeLapsed() const;
            double getSizeCancelled() const;
            double getSizeVoided() const;
            const std::string& getRegulatorAuthCode() const;
            const std::string& getRegulatorCode() const;
            const std::string& getCustomerOrderRef() const;
            const std::string& getCustomerStrategyRef() const;
            const CurrentItemDescription& getCurrentItemDescription() const;
            const std::string& getSourceIdKey() const;
            const std::string& getSourceIdDescription() const;

        private:
            std::string bet_id_;
            std::string market_id_;
            long selection_id_;
            double handicap_;
            PriceSize price_size_;
            double bsp_liability_;
            BetfairAPI::BettingEnum::Side side_;
            BetfairAPI::BettingEnum::OrderStatus status_;
            BetfairAPI::BettingEnum::PersistenceType persistence_type_;
            BetfairAPI::BettingEnum::OrderType order_type_;
            BetfairAPI::Utils::Date placed_date_;
            BetfairAPI::Utils::Date matched_date_;
            double average_price_matched_;
            double size_matched_;
            double size_remaining_;
            double size_lapsed_;
            double size_cancelled_;
            double size_voided_;
            std::string regulator_auth_code_;
            std::string regulator_code_;
            std::string customer_order_ref_;
            std::string customer_strategy_ref_;
            CurrentItemDescription current_item_description_;
            std::string source_id_key_;
            std::string source_id_description_;

    };
}