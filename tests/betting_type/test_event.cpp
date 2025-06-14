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

