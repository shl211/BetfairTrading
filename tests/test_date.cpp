#include <gtest/gtest.h>
#include "BetfairAPI/date.h"

class DateParamTest : public ::testing::TestWithParam<std::string> {};

TEST_P(DateParamTest, IsoStringRoundTrip) {
    std::string input = GetParam();
    BetfairAPI::Date date1{input};
    BetfairAPI::Date date2{date1.getIsoString()}; // round-trip string

    EXPECT_EQ(date1, date2);  // compares internal time_points, not strings
}

INSTANTIATE_TEST_SUITE_P(
    IsoStringTests,
    DateParamTest,
    ::testing::Values(
        "2024-06-01T12:34:56Z",
        "2020-01-01T00:00:00Z",
        "1999-12-31T23:59:59Z",
        "2015-05-20T08:15:30Z",
        "2024-06-01T14:34:56+02:00",
        "2024-06-01T07:34:56-05:00",
        "2024-06-01T07:34:56",
        "2024-06-01T07:34:59"
    )
);

TEST(DateComparisonTest, OperatorsWorkCorrectly) {
    // All times are in ISO8601 format
    BetfairAPI::Date date1("2024-07-10T12:00:00Z");
    BetfairAPI::Date date2("2024-07-10T12:00:00Z"); // Same as date1
    BetfairAPI::Date date3("2024-07-10T13:00:00Z"); // One hour later

    // Equality
    EXPECT_TRUE(date1 == date2);
    EXPECT_FALSE(date1 != date2);

    // Inequality
    EXPECT_TRUE(date1 != date3);
    EXPECT_FALSE(date1 == date3);

    // Less than
    EXPECT_TRUE(date1 < date3);
    EXPECT_FALSE(date3 < date1);

    // Greater than
    EXPECT_TRUE(date3 > date1);
    EXPECT_FALSE(date1 > date3);

    // Less than or equal
    EXPECT_TRUE(date1 <= date2);
    EXPECT_TRUE(date1 <= date3);
    EXPECT_FALSE(date3 <= date1);

    // Greater than or equal
    EXPECT_TRUE(date1 >= date2);
    EXPECT_TRUE(date3 >= date1);
    EXPECT_FALSE(date1 >= date3);
};