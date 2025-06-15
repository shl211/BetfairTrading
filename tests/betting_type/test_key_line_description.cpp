#include <vector>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>

#include <gtest/gtest.h>

#include "betting_type/key_line_description.h"

TEST(KeyLineDescription, ConstructorAndGetter) {
    std::vector<BetfairAPI::BettingType::KeyLineSelection> key_line{
        {12345,21.3}, {23498789798,122.2}, {12232,1}
    };

    BetfairAPI::BettingType::KeyLineDescription description(key_line);

    EXPECT_EQ(description.getKeyLine(),key_line);
}
TEST(KeyLineDescription, ConstructFromList) {
    std::list<BetfairAPI::BettingType::KeyLineSelection> key_line_list{
        {1, 2.5}, {2, 3.5}, {3, 4.5}
    };
    std::vector<BetfairAPI::BettingType::KeyLineSelection> key_line_vec(key_line_list.begin(), key_line_list.end());
    BetfairAPI::BettingType::KeyLineDescription description(key_line_vec);
    EXPECT_EQ(description.getKeyLine(), key_line_vec);
}

TEST(KeyLineDescription, ConstructFromArray) {
    std::array<BetfairAPI::BettingType::KeyLineSelection, 2> key_line_array{{
        {10, 1.1}, {20, 2.2}
    }};
    std::vector<BetfairAPI::BettingType::KeyLineSelection> key_line_vec(key_line_array.begin(), key_line_array.end());
    BetfairAPI::BettingType::KeyLineDescription description(key_line_vec);
    EXPECT_EQ(description.getKeyLine(), key_line_vec);
}

TEST(KeyLineDescription, ConstructFromDeque) {
    std::deque<BetfairAPI::BettingType::KeyLineSelection> key_line_deque{
        {100, 10.0}, {200, 20.0}
    };
    std::vector<BetfairAPI::BettingType::KeyLineSelection> key_line_vec(key_line_deque.begin(), key_line_deque.end());
    BetfairAPI::BettingType::KeyLineDescription description(key_line_vec);
    EXPECT_EQ(description.getKeyLine(), key_line_vec);
}
