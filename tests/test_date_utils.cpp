#include <gtest/gtest.h>
#include "utils/date_utils.h"

TEST(Date, ParsesAndFormatsIso8601Correctly) {
    // ISO8601 string with timezone offset and milliseconds
    std::string iso_string = "2025-06-14T15:04:05.123+02:00";

    BetfairAPI::Utils::Date date(iso_string);

    std::string formatted = date.toIsoString();

    // The formatted string should start with the original date/time portion
    // Timezone offset might be normalized but usually stays the same
    EXPECT_TRUE(formatted.find("2025-06-14T15:04:05") == 0);

    // It should contain the milliseconds part
    EXPECT_NE(formatted.find(".123"), std::string::npos);

    // It should end with the timezone offset "+02:00" (or equivalent)
    EXPECT_NE(formatted.find("+02:00"), std::string::npos);
}

/*
TEST(Date, ThrowsOnInvalidInput) {
    std::string invalidIso = "not-a-date";

    EXPECT_THROW({
        BetfairAPI::Utils::Date d(invalidIso);
    }, std::invalid_argument);
}
*/
TEST(Date, EqualityOperatorWorks) {
    std::string iso1 = "2025-06-14T15:04:05.123+02:00";
    std::string iso2 = "2025-06-14T15:04:05.123+02:00";
    BetfairAPI::Utils::Date date1(iso1);
    BetfairAPI::Utils::Date date2(iso2);

    EXPECT_TRUE(date1 == date2);
}

TEST(Date, InequalityOperatorWorks) {
    std::string iso1 = "2025-06-14T15:04:05.123+02:00";
    std::string iso2 = "2025-06-14T16:04:05.123+02:00"; // different hour
    BetfairAPI::Utils::Date date1(iso1);
    BetfairAPI::Utils::Date date2(iso2);

    EXPECT_TRUE(date1 != date2);
}