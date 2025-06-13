#include <gtest/gtest.h>

#include "betting_type/price_size.h"

TEST(PriceSize,ConstructorAndGetter) {
    double price = 1.23;
    double size = 100;

    BetfairAPI::BettingType::PriceSize ps(price,size);

    EXPECT_EQ(ps.getPrice(),price);
    EXPECT_EQ(ps.getSize(),size);
}

TEST(PriceSize,Equality) {
    EXPECT_TRUE(BetfairAPI::BettingType::PriceSize(0.5,0.67) == BetfairAPI::BettingType::PriceSize(0.5,0.67));
}

TEST(PriceSize,Inequality) {
    EXPECT_TRUE(BetfairAPI::BettingType::PriceSize(0.5,0.66) != BetfairAPI::BettingType::PriceSize(0.5,0.67));
}