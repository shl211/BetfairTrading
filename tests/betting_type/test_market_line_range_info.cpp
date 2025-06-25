#include <gtest/gtest.h>

#include "betting_type/market_line_range_info.h"

TEST(MarketLineRangeInfo,ConstructorAndGetter) {
    double min{1.0};
    double max{1.5};
    double interval{0.1};
    std::string unit{"goals"};
    BetfairAPI::BettingType::MarketLineRangeInfo info(max,min,interval,unit);
    
    EXPECT_DOUBLE_EQ(info.getInterval(), interval);
    EXPECT_DOUBLE_EQ(info.getMaxUnitValue(), max);
    EXPECT_DOUBLE_EQ(info.getMinUnitValue(), min);
    EXPECT_EQ(info.getMarketUnit(), unit);
}
TEST(MarketLineRangeInfo, EqualityOperator) {
    double min{1.0};
    double max{1.5};
    double interval{0.1};
    std::string unit{"goals"};
    BetfairAPI::BettingType::MarketLineRangeInfo info1(max, min, interval, unit);
    BetfairAPI::BettingType::MarketLineRangeInfo info2(max, min, interval, unit);

    EXPECT_TRUE(info1 == info2);
}

TEST(MarketLineRangeInfo, InequalityOperator) {
    double min{1.0};
    double max{1.5};
    double interval{0.1};
    std::string unit{"goals"};
    BetfairAPI::BettingType::MarketLineRangeInfo info1(max, min, interval, unit);
    BetfairAPI::BettingType::MarketLineRangeInfo info2(max, min, 0.2, unit);

    EXPECT_TRUE(info1 != info2);
}
