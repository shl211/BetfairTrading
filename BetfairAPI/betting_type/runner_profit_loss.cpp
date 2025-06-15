#include "runner_profit_loss.h"
#include "utils/math_utils.hpp"

namespace BetfairAPI::BettingType {
    RunnerProfitLoss::RunnerProfitLoss(long selection_id, double if_win, double if_lose, double if_place)
        : selection_id_(selection_id), if_win_(if_win), if_lose_(if_lose), if_place_(if_place) {}


    bool RunnerProfitLoss::operator==(const RunnerProfitLoss& other) const {
        return selection_id_ == other.selection_id_ && 
                BetfairAPI::Utils::almostEqual(if_win_,other.if_win_) &&
                BetfairAPI::Utils::almostEqual(if_lose_,other.if_lose_) &&
                BetfairAPI::Utils::almostEqual(if_place_,other.if_place_);
    }

    bool RunnerProfitLoss::operator!=(const RunnerProfitLoss& other) const {
        return !(*this == other);
    }

    long RunnerProfitLoss::getSelectionId() const {
        return selection_id_;
    }

    double RunnerProfitLoss::getIfWin() const {
        return if_win_;
    }

    double RunnerProfitLoss::getIfLose() const {
        return if_lose_;
    }

    double RunnerProfitLoss::getIfPlace() const {
        return if_place_;
    }
}