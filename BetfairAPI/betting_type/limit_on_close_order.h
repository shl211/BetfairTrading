#pragma once

namespace BetfairAPI::BettingType {
    class LimitOnCloseOrder {
        public:
            LimitOnCloseOrder(double liability, double price);
            LimitOnCloseOrder() = default;
            ~LimitOnCloseOrder() = default;
            LimitOnCloseOrder(const LimitOnCloseOrder&) = default;
            LimitOnCloseOrder(LimitOnCloseOrder&&) noexcept = default;
            LimitOnCloseOrder& operator=(const LimitOnCloseOrder&) = default;
            LimitOnCloseOrder& operator=(LimitOnCloseOrder&&) noexcept= default;
        
            bool operator==(const LimitOnCloseOrder& other) const;
            bool operator!=(const LimitOnCloseOrder& other) const;

            double getLiability() const;
            double getPrice() const;

        private:
            double liability_;
            double price_;
    };
}