#include <gtest/gtest.h>

#include "utils/enum_utils.hpp"
#include <stdexcept>

TEST(EnumUtils, ToString) {
    enum class TEST_ENUM {A,B,C,D,SOMETHING_ELSE};
    
    EXPECT_EQ(BetfairAPI::Utils::to_string(TEST_ENUM::A), "A");
    EXPECT_EQ(BetfairAPI::Utils::to_string(TEST_ENUM::B), "B");
    EXPECT_EQ(BetfairAPI::Utils::to_string(TEST_ENUM::C), "C");
    EXPECT_EQ(BetfairAPI::Utils::to_string(TEST_ENUM::D), "D");
    EXPECT_EQ(BetfairAPI::Utils::to_string(TEST_ENUM::SOMETHING_ELSE), "SOMETHING_ELSE");
}

TEST(EnumUtils, FromString) {
    enum class TEST_ENUM {A,B,C,D,SOMETHING_ELSE};
    
    //check for valid cases
    EXPECT_EQ(BetfairAPI::Utils::from_string<TEST_ENUM>("A"), TEST_ENUM::A);
    EXPECT_EQ(BetfairAPI::Utils::from_string<TEST_ENUM>("B"), TEST_ENUM::B);
    EXPECT_EQ(BetfairAPI::Utils::from_string<TEST_ENUM>("C"), TEST_ENUM::C);
    EXPECT_EQ(BetfairAPI::Utils::from_string<TEST_ENUM>("D"), TEST_ENUM::D);
    EXPECT_EQ(BetfairAPI::Utils::from_string<TEST_ENUM>("SOMETHING_ELSE"), TEST_ENUM::SOMETHING_ELSE);

    //check for invalid cases
    ASSERT_THROW(BetfairAPI::Utils::from_string<TEST_ENUM>("a"), std::invalid_argument);
    ASSERT_THROW(BetfairAPI::Utils::from_string<TEST_ENUM>("Ab"), std::invalid_argument);
    ASSERT_THROW(BetfairAPI::Utils::from_string<TEST_ENUM>("Something_Else"), std::invalid_argument);

    enum class TEST_ENUM_OTHER {E};
    ASSERT_THROW(BetfairAPI::Utils::from_string<TEST_ENUM>("E"), std::invalid_argument);
}