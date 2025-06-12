#include <gtest/gtest.h>

#include "BettingType/PriceSize.h"

TEST(PriceSize,ConstructorAndGetter) {
    double price = 1.23;
    double size = 100;

    BetfairAPI::BettingType::PriceSize ps(price,size);

    EXPECT_EQ(ps.getPrice(),price);
    EXPECT_EQ(ps.getSize(),size);
}