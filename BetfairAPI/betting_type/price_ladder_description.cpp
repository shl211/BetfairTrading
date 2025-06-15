#include "price_ladder_description.h"

namespace BetfairAPI::BettingType {

    PriceLadderDescription::PriceLadderDescription(BetfairAPI::BettingEnum::PriceLadderType type)
        : type_(type) {}

    BetfairAPI::BettingEnum::PriceLadderType PriceLadderDescription::getType() {
        return type_;
    }
}