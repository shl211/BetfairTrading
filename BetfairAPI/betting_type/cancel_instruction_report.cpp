#include "cancel_instruction_report.h"

namespace BetfairAPI::BettingType {
    CancelInstructionReport::CancelInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status, double size_cancelled)
        : status_(status), size_cancelled_(size_cancelled) {}

    void CancelInstructionReport::setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e) {
        error_code_ = e;
    }

    void CancelInstructionReport::setInstruction(CancelInstruction instruction) {
        instruction_ = std::move(instruction);
    }

    void CancelInstructionReport::setCancelledDate(BetfairAPI::Utils::Date date) {
        cancelled_date_ = std::move(date);
    }

    BetfairAPI::BettingEnum::InstructionReportStatus CancelInstructionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::InstructionReportErrorCode CancelInstructionReport::getErrorCode() const {
        return error_code_;
    }

    const std::optional<CancelInstruction>& CancelInstructionReport::getInstruction() const {
        return instruction_;
    }

    double CancelInstructionReport::getSizeCancelled() const {
        return size_cancelled_;
    }

    const BetfairAPI::Utils::Date& CancelInstructionReport::getCancelledDate() const {
        return cancelled_date_;
    }
}