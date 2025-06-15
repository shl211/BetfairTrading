#include <gtest/gtest.h>

#include "betting_type/update_instruction_report.h"

TEST(UpdateInstructionReport,ConstructorAndGetter) {

    BetfairAPI::BettingEnum::InstructionReportStatus status = BetfairAPI::BettingEnum::InstructionReportStatus::SUCCESS;
    BetfairAPI::BettingEnum::InstructionReportErrorCode e = BetfairAPI::BettingEnum::InstructionReportErrorCode::BET_IN_PROGRESS;
    BetfairAPI::BettingType::UpdateInstruction instruction("12345", BetfairAPI::BettingEnum::PersistenceType::LAPSE);

    BetfairAPI::BettingType::UpdateInstructionReport report(status,e,instruction);

    // Test getters return correct values
    EXPECT_EQ(report.getStatus(), status);
    EXPECT_EQ(report.getErrorCode(), e);
    EXPECT_EQ(report.getInstruction(), instruction);
}