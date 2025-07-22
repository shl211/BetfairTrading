#include <gtest/gtest.h>

#include "BetfairAPI/utils.h"

TEST(Utils,EnumToString) {    
    enum class Color { Red, Green, Blue };
    EXPECT_EQ(BetfairAPI::to_string(Color::Red), "Red");
    EXPECT_EQ(BetfairAPI::to_string(Color::Green), "Green");
    EXPECT_EQ(BetfairAPI::to_string(Color::Blue), "Blue");
}

TEST(Utils, EnumFromStringValid) {
    enum class Color { Red, Green, Blue };
    EXPECT_EQ(BetfairAPI::from_string<Color>("Red"), Color::Red);
    EXPECT_EQ(BetfairAPI::from_string<Color>("Green"), Color::Green);
    EXPECT_EQ(BetfairAPI::from_string<Color>("Blue"), Color::Blue);
}

TEST(Utils, EnumFromStringInvalid) {
    enum class Color { Red, Green, Blue };
    EXPECT_THROW(BetfairAPI::from_string<Color>("Yellow"), std::invalid_argument);
}

TEST(Utils, VectorOfEnumToString) {
    enum class Color { Red, Green, Blue };
    std::vector<Color> colors = {Color::Red, Color::Green, Color::Blue};
    std::vector<std::string> expected_colors {"Red","Green","Blue"};
    EXPECT_EQ(BetfairAPI::to_string(colors), expected_colors);
}

TEST(Utils, SetOfEnumToString) {
    enum class Color { Red, Green, Blue };
    std::set<Color> colors = {Color::Green, Color::Red};
    std::set<std::string> expected_colors {"Green","Red"};
    EXPECT_EQ(BetfairAPI::to_string(colors), expected_colors);
}

TEST(Utils, VectorOfEnumFromString) {
    enum class Color { Red, Green, Blue };
    std::vector<std::string> vec {"Red","Green","Blue","Blue"};
    auto result = BetfairAPI::from_string<Color>(vec);
    std::vector<Color> expected = {Color::Red, Color::Green, Color::Blue, Color::Blue};
    EXPECT_EQ(result, expected);
}

TEST(Utils, SetOfEnumFromString) {
    enum class Color { Red, Green, Blue };
    std::set<std::string> vec {"Green","Red"};
    auto result = BetfairAPI::from_string<Color>(vec);
    std::set<Color> expected = {Color::Green, Color::Red};
    EXPECT_EQ(result, expected);
}