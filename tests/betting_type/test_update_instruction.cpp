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