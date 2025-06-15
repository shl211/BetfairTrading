#include "key_line_description.h"

namespace BetfairAPI::BettingType {

    KeyLineDescription::KeyLineDescription(const std::vector<KeyLineSelection>& key_line)
        : key_line_(key_line) {}

    const std::vector<KeyLineSelection>& KeyLineDescription::getKeyLine() const {
        return key_line_;
    }
}

#include "key_line_description.tpp"