#include "exchange_prices.h"
#include <iostream>
namespace BetfairAPI::BettingType {
    ExchangePrices::ExchangePrices(const std::vector<PriceSize>& available_to_back, 
                const std::vector<PriceSize>& available_to_lay, const std::vector<PriceSize>& traded_volume)
                    : available_to_back_(available_to_back), available_to_lay_(available_to_lay), traded_volume_(traded_volume) {};
}