#pragma once

#include <vector>

#include "price_size.h"

namespace BetfairAPI::BettingType {
    class ExchangePrices {
        public:
            ExchangePrices(const std::vector<PriceSize>& available_to_back, 
                const std::vector<PriceSize>& available_to_lay, const std::vector<PriceSize>& traded_volume);
            
            template <typename Iterable1, typename Iterable2, typename Iterable3>
            ExchangePrices(const Iterable1& available_to_back, const Iterable2& available_to_lay,
                const Iterable3& traded_volume);

            ~ExchangePrices() = default;

            ExchangePrices(const ExchangePrices&) = default;
            ExchangePrices(ExchangePrices&&) noexcept = default;
            ExchangePrices& operator=(const ExchangePrices&) = default;
            ExchangePrices& operator=(ExchangePrices&&) noexcept = default;

            const std::vector<PriceSize>& getAvailableToBack() const;
            const std::vector<PriceSize>& getAvailableToLay() const;
            const std::vector<PriceSize>& getTradedVolume() const;
            //might be better to access it as sets of 3?


        private:
            std::vector<PriceSize> available_to_back_;
            std::vector<PriceSize> available_to_lay_;
            std::vector<PriceSize> traded_volume_;
    };
}

#include "exchange_prices.tpp"