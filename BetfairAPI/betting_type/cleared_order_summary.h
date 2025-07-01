#pragma once

#include <string>
#include "utils/date_utils.h"
#include "betting_enum/persistence_type.hpp"
#include "betting_enum/order_type.hpp"
#include "betting_enum/side.hpp"
#include "item_description.h"

namespace BetfairAPI::BettingType {
    class ClearedOrderSummary {
        public:
        ClearedOrderSummary() = default;
        ~ClearedOrderSummary() = default;
        ClearedOrderSummary(const ClearedOrderSummary&) = default;
        ClearedOrderSummary(ClearedOrderSummary&&) noexcept = default;
        ClearedOrderSummary& operator=(const ClearedOrderSummary&) = default;
        ClearedOrderSummary& operator=(ClearedOrderSummary&&) noexcept = default;

        friend std::ostream& operator<<(std::ostream& os, const ClearedOrderSummary& summary);

        // Getters
        const std::string& getEventTypeId() const;
        const std::string& getEventId() const;
        const std::string& getMarketId() const;
        long getSelectionId() const;
        double getHandicap() const;
        const std::string& getBetId() const;
        const BetfairAPI::Utils::Date& getPlacedDate() const;
        BetfairAPI::BettingEnum::PersistenceType getPersistenceType() const;
        BetfairAPI::BettingEnum::OrderType getOrderType() const;
        BetfairAPI::BettingEnum::Side getSide() const;
        const ItemDescription& getItemDescription() const;
        const std::string& getBetOutcome() const;
        double getPriceRequested() const;
        const BetfairAPI::Utils::Date& getSettledDate() const;
        const BetfairAPI::Utils::Date& getLastMatchedDate() const;
        int getBetCount() const;
        double getCommission() const;
        double getPriceMatched() const;
        bool getPriceReduced() const;
        double getSizeSettled() const;
        double getProfit() const;
        double getSizeCancelled() const;
        const std::string& getCustomerOrderRef() const;
        const std::string& getCustomerStrategyRef() const;
        const std::string& getSourceIdKey() const;
        const std::string& getSourceIdDescription() const;

        // Setters
        void setEventTypeId(const std::string& event_type_id);
        void setEventId(const std::string& event_id);
        void setMarketId(const std::string& market_id);
        void setSelectionId(long selection_id);
        void setHandicap(double handicap);
        void setBetId(const std::string& bet_id);
        void setPlacedDate(const BetfairAPI::Utils::Date& placed_date);
        void setPersistenceType(BetfairAPI::BettingEnum::PersistenceType persistence_type);
        void setOrderType(BetfairAPI::BettingEnum::OrderType order_type);
        void setSide(BetfairAPI::BettingEnum::Side side);
        void setItemDescription(const ItemDescription& item_description);
        void setBetOutcome(const std::string& bet_outcome);
        void setPriceRequested(double price_requested);
        void setSettledDate(const BetfairAPI::Utils::Date& settled_date);
        void setLastMatchedDate(const BetfairAPI::Utils::Date& last_matched_date);
        void setBetCount(int bet_count);
        void setCommission(double commission);
        void setPriceMatched(double price_matched);
        void setPriceReduced(bool price_reduced);
        void setSizeSettled(double size_settled);
        void setProfit(double profit);
        void setSizeCancelled(double size_cancelled);
        void setCustomerOrderRef(const std::string& customer_order_ref);
        void setCustomerStrategyRef(const std::string& customer_strategy_ref);
        void setSourceIdKey(const std::string& source_id_key);
        void setSourceIdDescription(const std::string& source_id_description);

        private:
            std::string event_type_id_{};
            std::string event_id_{};
            std::string market_id_{};
            long selection_id_{0};
            double handicap_{0.0};
            std::string bet_id_{};
            BetfairAPI::Utils::Date placed_date_{};
            BetfairAPI::BettingEnum::PersistenceType persistence_type_{BetfairAPI::BettingEnum::PersistenceType::UNKNOWN};
            BetfairAPI::BettingEnum::OrderType order_type_{BetfairAPI::BettingEnum::OrderType::UNKNOWN};
            BetfairAPI::BettingEnum::Side side_{BetfairAPI::BettingEnum::Side::UNKNOWN};
            ItemDescription item_description_{};
            std::string bet_outcome_{};
            double price_requested_{0.0};
            BetfairAPI::Utils::Date settled_date_{};
            BetfairAPI::Utils::Date last_matched_date_{};
            int bet_count_{0};
            double commission_{0.0};
            double price_matched_{0.0};
            bool price_reduced_{false};
            double size_settled_{0.0};
            double profit_{0.0};
            double size_cancelled_{0.0};
            std::string customer_order_ref_{};
            std::string customer_strategy_ref_{};
            std::string source_id_key_{};
            std::string source_id_description_{};
    };
}