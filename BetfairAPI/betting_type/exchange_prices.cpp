#include "exchange_prices.h"
#include <iostream>
namespace BetfairAPI::BettingType {
    ExchangePrices::ExchangePrices(const std::vector<PriceSize>& available_to_back, 
                const std::vector<PriceSize>& available_to_lay, const std::vector<PriceSize>& traded_volume)
                    : available_to_back_(available_to_back), available_to_lay_(available_to_lay), traded_volume_(traded_volume) {};
    
    const std::vector<PriceSize>& ExchangePrices::getAvailableToBack() const {
        return available_to_back_;
    }

    const std::vector<PriceSize>& ExchangePrices::getAvailableToLay() const {
        return available_to_lay_;
    }

    const std::vector<PriceSize>& ExchangePrices::getTradedVolume() const {
        return traded_volume_;
    }
}