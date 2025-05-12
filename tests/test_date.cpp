#include <gtest/gtest.h>
#include "Date.h"

class DateConstructorValid : public ::testing::TestWithParam<std::tuple<int, BetfairAPI::Month, int>> {
};

TEST_P(DateConstructorValid, ConstructsWithoutThrowing) {
    auto [year, month, day] = GetParam();
    EXPECT_NO_THROW({
        BetfairAPI::Date date(year, month, day);
    });
}

INSTANTIATE_TEST_SUITE_P(
    ValidDates,
    DateConstructorValid,
    ::testing::Values(
        std::make_tuple(2020, BetfairAPI::Month::February, 29),  // Leap year
        std::make_tuple(2021, BetfairAPI::Month::December, 31),
        std::make_tuple(2000, BetfairAPI::Month::January, 1),
        std::make_tuple(1999, BetfairAPI::Month::June,15)
    )
);

