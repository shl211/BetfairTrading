#pragma once

namespace BetfairAPI::BettingType {
    class PriceSize {
        public:
            PriceSize(double price, double size);
            ~PriceSize() = default;

            double getPrice() const;
            double getSize() const;

        private:
            double price_;//The price available
            double size_;//The stake available
    };
}