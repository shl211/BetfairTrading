#include "current_item_description.h"
#include <utility>

namespace BetfairAPI::BettingType {

    CurrentItemDescription::CurrentItemDescription(MarketVersion v)
        : market_version_(std::move(v)) {}

    MarketVersion CurrentItemDescription::getMarketVersion() const {
        return market_version_;
    }

}