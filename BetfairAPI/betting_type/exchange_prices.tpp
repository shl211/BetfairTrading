#include <algorithm>
#include <iostream>

namespace BetfairAPI::BettingType {
    template<typename Iterable1, typename Iterable2, typename Iterable3>
    ExchangePrices::ExchangePrices(const Iterable1& available_to_back, const Iterable2& available_to_lay, const Iterable3& traded_volume)
        : available_to_back_(available_to_back.begin(), available_to_back.end()),
        available_to_lay_(available_to_lay.begin(), available_to_lay.end()),
        traded_volume_(traded_volume.begin(), traded_volume.end())
    {}
}