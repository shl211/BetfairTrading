#include "replace_instruction_report.h"

namespace BetfairAPI::BettingType {
    ReplaceInstructionReport::ReplaceInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status) 
        : status_(status) {}

    void ReplaceInstructionReport::setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e) {
        error_code_ = e;
    }

    void ReplaceInstructionReport::setCancelInstructionReport(CancelInstructionReport report) {
        cancel_instruction_report_ = std::move(report);
    }

    void ReplaceInstructionReport::setPlaceInstructionReport(PlaceInstructionReport report) {
        place_instruction_report_ = std::move(report);
    }

    BetfairAPI::BettingEnum::InstructionReportStatus ReplaceInstructionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::InstructionReportErrorCode ReplaceInstructionReport::getErrorCode() const {
        return error_code_;
    }

    const CancelInstructionReport& ReplaceInstructionReport::getCancelInstructionReport() const {
        return cancel_instruction_report_;
    }

    const PlaceInstructionReport& ReplaceInstructionReport::getPlaceInstructionReport() const {
        return place_instruction_report_;
    }

}