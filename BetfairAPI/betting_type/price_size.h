#pragma once

namespace BetfairAPI::BettingType {
    class PriceSize {
        public:
            PriceSize(double price, double size);
            ~PriceSize() = default;
            PriceSize(const PriceSize&) = default;
            PriceSize(PriceSize&&) noexcept= default;
            PriceSize& operator=(const PriceSize&) = default;
            PriceSize& operator=(PriceSize&&) noexcept = default;
            
            bool operator==(const PriceSize& other) const;
            bool operator!=(const PriceSize& other) const;

            double getPrice() const;
            double getSize() const;

        private:
            double price_;//The price available
            double size_;//The stake available
    };
}