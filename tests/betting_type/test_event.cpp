#include <gtest/gtest.h>

#include "betting_type/event.h"

TEST (Event, ConstructorAndGetter){
    std::string id = "12345";
    std::string name = "Football Match";
    std::string country_code = "GB";
    std::string timezone = "GMT";
    std::string venue = "Wembley";
    BetfairAPI::Utils::Date open_date = BetfairAPI::Utils::Date("2024-06-10T15:30:00Z");

    BetfairAPI::BettingType::Event event(id, name, country_code, timezone, venue, open_date);

    EXPECT_EQ(event.getId(), id);
    EXPECT_EQ(event.getName(), name);
    EXPECT_EQ(event.getCountryCode(), country_code);
    EXPECT_EQ(event.getTimezone(), timezone);
    EXPECT_EQ(event.getVenue(), venue);
    EXPECT_EQ(event.getDate(), open_date);
}
TEST(Event, EqualityOperator) {
    std::string id = "12345";
    std::string name1 = "Football Match";
    std::string name2 = "Tennis Match";
    std::string country_code = "GB";
    std::string timezone = "GMT";
    std::string venue = "Wembley";
    BetfairAPI::Utils::Date open_date = BetfairAPI::Utils::Date("2024-06-10T15:30:00Z");

    BetfairAPI::BettingType::Event event1(id, name1, country_code, timezone, venue, open_date);
    BetfairAPI::BettingType::Event event2(id, name2, country_code, timezone, venue, open_date);

    // Same id, should be equal
    EXPECT_TRUE(event1 == event2);
}

TEST(Event, InequalityOperator) {
    std::string id1 = "12345";
    std::string id2 = "67890";
    std::string name = "Football Match";
    std::string country_code = "GB";
    std::string timezone = "GMT";
    std::string venue = "Wembley";
    BetfairAPI::Utils::Date open_date = BetfairAPI::Utils::Date("2024-06-10T15:30:00Z");

    BetfairAPI::BettingType::Event event1(id1, name, country_code, timezone, venue, open_date);
    BetfairAPI::BettingType::Event event2(id2, name, country_code, timezone, venue, open_date);

    // Different id, should not be equal
    EXPECT_TRUE(event1 != event2);
}
