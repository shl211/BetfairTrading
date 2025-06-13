#include <gtest/gtest.h>

#include "betting_type/starting_prices.h"

TEST(StartingPrices,ConstructorAndGetter) {

    double near_price {1.32};
    double far_price {32};
    double actual_sp {12.0};
    std::vector<BetfairAPI::BettingType::PriceSize> back_taken {{1,1},{2.1,100}};
    std::vector<BetfairAPI::BettingType::PriceSize> lay_taken {{1,2}};

    BetfairAPI::BettingType::StartingPrices prices(near_price,far_price,actual_sp,back_taken,lay_taken);

    EXPECT_EQ(prices.getNearPrice(),near_price);
    EXPECT_EQ(prices.getFarPrice(),far_price);
    EXPECT_EQ(prices.getActualSP(),actual_sp);
    EXPECT_EQ(prices.getBackStakeTaken(),back_taken);
    EXPECT_EQ(prices.getLayLiabilityTaken(),lay_taken);
}
