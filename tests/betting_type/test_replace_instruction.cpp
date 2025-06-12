#include <gtest/gtest.h>

#include "betting_type/replace_instruction.h"

TEST(ReplaceInstruction, ConstructorAndGetter) {
    std::string bet_id = "123435";
    double new_price = 0.67;

    BetfairAPI::BettingType::ReplaceInstruction instruction(bet_id,new_price);

    EXPECT_EQ(instruction.getBetId(),bet_id);
    EXPECT_EQ(instruction.getNewPrice(),new_price);
}