#pragma once

#include "betting_enum/persistence_type.hpp"
#include "betting_enum/time_in_force.hpp"
#include "betting_enum/bet_target_type.hpp"

namespace BetfairAPI::BettingType {
    class LimitOrder {
        public:
            LimitOrder(double size,double price, BetfairAPI::BettingEnum::PersistenceType persistence_type,
                BetfairAPI::BettingEnum::TimeInForce time_in_force,double min_fill_size,
                BetfairAPI::BettingEnum::BetTargetType bet_target_type, double bet_target_size);
            ~LimitOrder() = default;
            LimitOrder(const LimitOrder&) = default;
            LimitOrder(LimitOrder&&) noexcept = default;
            LimitOrder& operator=(const LimitOrder&) = default;
            LimitOrder& operator=(LimitOrder&&) noexcept = default;

            bool operator==(const LimitOrder& other) const;
            bool operator!=(const LimitOrder& other) const;

            double getSize() const;
            double getPrice() const;
            BetfairAPI::BettingEnum::PersistenceType getPersistenceType() const;
            BetfairAPI::BettingEnum::TimeInForce getTimeInForce() const;
            double getMinFillSize() const;
            BetfairAPI::BettingEnum::BetTargetType getBetTargetType() const;
            double getBetTargetSize() const;

        private:
            double size_;
            double price_;
            BetfairAPI::BettingEnum::PersistenceType persistence_type_;
            BetfairAPI::BettingEnum::TimeInForce time_in_force_;
            double min_fill_size_;
            BetfairAPI::BettingEnum::BetTargetType bet_target_type_;
            double bet_target_size_;
    };
}