#pragma once 

#include <string>
#include "betting_enum/order_type.hpp"
#include "betting_enum/order_status.hpp"
#include "betting_enum/persistence_type.hpp"
#include "betting_enum/side.hpp"
#include "utils/date_utils.h"

namespace BetfairAPI::BettingType {
    struct OrderParams {
        std::string bet_id;
        BetfairAPI::BettingEnum::OrderType order_type;
        BetfairAPI::BettingEnum::OrderStatus order_status;
        BetfairAPI::BettingEnum::PersistenceType persistence_type;
        BetfairAPI::BettingEnum::Side side;
        double price;
        double size;
        double bsp_liability;
        BetfairAPI::Utils::Date placed_date;
        double avg_price_matched;
        double size_matched;
        double size_remaining;
        double size_lapsed;
        double size_cancelled;
        double size_voided;
        std::string customer_order_ref;
        std::string customer_strategy_ref;
    };
    
    class Order {
        public:
            Order(const OrderParams& params);
            Order() = default;
            ~Order() = default;

            std::string getBetId() const;
            BetfairAPI::BettingEnum::OrderType getOrderType() const;
            BetfairAPI::BettingEnum::OrderStatus getOrderStatus() const;
            BetfairAPI::BettingEnum::PersistenceType getPersistenceType() const;
            BetfairAPI::BettingEnum::Side getSide() const;
            double getPrice() const;
            double getSize() const;
            double getBspLiability() const;
            const BetfairAPI::Utils::Date& getPlacedDate() const;
            double getAvgPriceMatched() const;
            double getSizeMatched() const;
            double getSizeRemaining() const;
            double getSizeLapsed() const;
            double getSizeCancelled() const;
            double getSizeVoided() const;
            std::string getCustomerOrderRef() const;
            std::string getCustomerStrategyRef() const;

        private:
            std::string bet_id_;
            BetfairAPI::BettingEnum::OrderType order_type_;
            BetfairAPI::BettingEnum::OrderStatus order_status_;
            BetfairAPI::BettingEnum::PersistenceType persistence_type_;
            BetfairAPI::BettingEnum::Side side_;
            double price_;
            double size_;
            double bsp_liability_;
            BetfairAPI::Utils::Date placed_date_;
            double avg_price_matched_;
            double size_matched_;
            double size_remaining_;
            double size_lapsed_;
            double size_cancelled_;
            double size_voided_;
            std::string customer_order_ref_;
            std::string customer_strategy_ref_;
    };
}