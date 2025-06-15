#include "key_line_selection.h"
#include "utils/math_utils.hpp"

namespace BetfairAPI::BettingType {

    KeyLineSelection::KeyLineSelection(long selection_id, double handicap)
        : selection_id_(selection_id), handicap_(handicap) {}

    bool KeyLineSelection::operator==(const KeyLineSelection& other) const {
        return selection_id_ == other.selection_id_ && BetfairAPI::Utils::almostEqual(handicap_,other.handicap_);
    }

    bool KeyLineSelection::operator!=(const KeyLineSelection& other) const {
        return !(*this == other);
    }

    long KeyLineSelection::getSelectionId() {
        return selection_id_;
    }

    double KeyLineSelection::getHandicap() {
        return handicap_;
    }
}