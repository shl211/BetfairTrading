#include "place_instruction_report.h"

namespace BetfairAPI::BettingType {
    PlaceInstructionReport::PlaceInstructionReport(BetfairAPI::BettingEnum::InstructionReportStatus status,
        PlaceInstruction instruction)
            : status_(status), instruction_(std::move(instruction)) {}

    void PlaceInstructionReport::setErrorCode(BetfairAPI::BettingEnum::InstructionReportErrorCode e) {
        error_code_ = e;
    }

    void PlaceInstructionReport::setOrderStatus(BetfairAPI::BettingEnum::OrderStatus status) {
        order_status_ = status;
    }

    void PlaceInstructionReport::setBetId(std::string_view id) {
        bet_id_ = std::string(id);
    }

    void PlaceInstructionReport::setPlacedDate(BetfairAPI::Utils::Date date) {
        placed_date_ = std::move(date);
    }

    void PlaceInstructionReport::setAveragePriceMatched(double val) {
        average_price_matched_ = val;
    }

    void PlaceInstructionReport::setSizeMatched(double val) {
        size_matched_ = val;
    }

    BetfairAPI::BettingEnum::InstructionReportStatus PlaceInstructionReport::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::InstructionReportErrorCode PlaceInstructionReport::getErrorCode() const {
        return error_code_;
    }

    BetfairAPI::BettingEnum::OrderStatus PlaceInstructionReport::getOrderStatus() const {
        return order_status_;
    }

    const PlaceInstruction& PlaceInstructionReport::getInstruction() const {
        return instruction_;
    }

    const std::string& PlaceInstructionReport::getBetId() const {
        return bet_id_;
    }

    const BetfairAPI::Utils::Date& PlaceInstructionReport::getPlacedDate() const {
        return placed_date_;
    }

    double PlaceInstructionReport::getAveragePriceMatched() const {
        return average_price_matched_;
    }

    double PlaceInstructionReport::getSizeMatched() const {
        return size_matched_;
    }
}