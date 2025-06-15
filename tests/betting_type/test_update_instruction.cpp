#include <gtest/gtest.h>

#include "betting_type/update_instruction.h"
#include "betting_enum/persistence_type.hpp"

TEST(UpdateInstruction, ConstructorAndGetter) {
    std::string bet_id = "12345";
    BetfairAPI::BettingEnum::PersistenceType p_type = BetfairAPI::BettingEnum::PersistenceType::LAPSE;

    BetfairAPI::BettingType::UpdateInstruction update_instruction(bet_id,p_type);

    EXPECT_EQ(update_instruction.getBetId(),bet_id);
    EXPECT_EQ(update_instruction.getNewPersistenceType(),p_type);
}

TEST(UpdateInstruction, EqualityOperator) {
    std::string bet_id1 = "12345";
    std::string bet_id2 = "67890";
    auto p_type1 = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    auto p_type2 = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    BetfairAPI::BettingType::UpdateInstruction instr1(bet_id1, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr2(bet_id1, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr3(bet_id2, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr4(bet_id1, p_type2);

    EXPECT_TRUE(instr1 == instr2);
    EXPECT_FALSE(instr1 == instr3);
    EXPECT_FALSE(instr1 == instr4);
}

TEST(UpdateInstruction, InequalityOperator) {
    std::string bet_id1 = "12345";
    std::string bet_id2 = "67890";
    auto p_type1 = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    auto p_type2 = BetfairAPI::BettingEnum::PersistenceType::PERSIST;

    BetfairAPI::BettingType::UpdateInstruction instr1(bet_id1, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr2(bet_id1, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr3(bet_id2, p_type1);
    BetfairAPI::BettingType::UpdateInstruction instr4(bet_id1, p_type2);

    EXPECT_FALSE(instr1 != instr2);
    EXPECT_TRUE(instr1 != instr3);
    EXPECT_TRUE(instr1 != instr4);
}
