#include "runner_id.h"

namespace BetfairAPI::BettingType {

    RunnerId::RunnerId(std::string_view market_id, std::string_view selection_id, double handicap)
        : market_id_(market_id), selection_id_(selection_id), handicap_(handicap) {}

    bool RunnerId::operator==(const RunnerId& other) const {
        return market_id_ == other.market_id_ &&
            selection_id_ == other.selection_id_;
    }

    bool RunnerId::operator!=(const RunnerId& other) const {
        return !(*this == other);
    }

    const std::string& RunnerId::getMarketId() const {
        return market_id_;
    }

    const std::string& RunnerId::getSelectionId() const {
        return selection_id_;
    }

    double RunnerId::getHandicap() const {
        return handicap_;
    }

}