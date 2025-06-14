#include "gtest/gtest.h"

#include "betting_type/market_rates.h"

TEST(MarketRates, ConstructorAndGetter) {
    double base_rate{1.0};
    bool discount_allowed{true};

    BetfairAPI::BettingType::MarketRates rate(base_rate,discount_allowed);

    EXPECT_DOUBLE_EQ(rate.getMarketBaseRate(),base_rate);
    EXPECT_EQ(rate.isDiscountAllowed(),discount_allowed);
}