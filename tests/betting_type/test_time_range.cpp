#include <gtest/gtest.h>

#include "betting_type/time_range.h"

TEST(TimeRange,ConstructorAndGetter) {

    BetfairAPI::Utils::Date from("2021-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to("2024-06-01T00:00:00Z");

    BetfairAPI::BettingType::TimeRange tr(from,to);

    EXPECT_EQ(tr.getFromDate(), from);
    EXPECT_EQ(tr.getToDate(), to);
}

TEST(TimeRange, EqualityOperator) {
    BetfairAPI::Utils::Date from1("2021-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to1("2024-06-01T00:00:00Z");
    BetfairAPI::Utils::Date from2("2021-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to2("2024-06-01T00:00:00Z");

    BetfairAPI::BettingType::TimeRange tr1(from1, to1);
    BetfairAPI::BettingType::TimeRange tr2(from2, to2);

    EXPECT_TRUE(tr1 == tr2);
}

TEST(TimeRange, InequalityOperator_DifferentFromDate) {
    BetfairAPI::Utils::Date from1("2021-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to("2024-06-01T00:00:00Z");
    BetfairAPI::Utils::Date from2("2022-06-01T00:00:00Z");

    BetfairAPI::BettingType::TimeRange tr1(from1, to);
    BetfairAPI::BettingType::TimeRange tr2(from2, to);

    EXPECT_TRUE(tr1 != tr2);
}

TEST(TimeRange, InequalityOperator_DifferentToDate) {
    BetfairAPI::Utils::Date from("2021-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to1("2024-06-01T00:00:00Z");
    BetfairAPI::Utils::Date to2("2025-06-01T00:00:00Z");

    BetfairAPI::BettingType::TimeRange tr1(from, to1);
    BetfairAPI::BettingType::TimeRange tr2(from, to2);

    EXPECT_TRUE(tr1 != tr2);
}
