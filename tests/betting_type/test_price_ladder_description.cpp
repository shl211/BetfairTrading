#include <gtest/gtest.h>
#include "betting_type/price_ladder_description.h"

TEST(PriceLadderDescription,ConstructorAndGetter) {
    BetfairAPI::BettingEnum::PriceLadderType type = BetfairAPI::BettingEnum::PriceLadderType::CLASSIC;

    BetfairAPI::BettingType::PriceLadderDescription price_ladder(type);

    ASSERT_EQ(price_ladder.getType(),type);
}