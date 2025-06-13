#include "competition.h"

namespace BetfairAPI::BettingType {
    Competition::Competition(std::string_view id, std::string_view name) 
        : id_(id), name_(name) {};

    bool Competition::operator==(const Competition& other) const {
        return id_ == other.id_;
    }

    bool Competition::operator!=(const Competition& other) const {
        return !(*this == other);
    }

    std::string Competition::getId() const {
        return id_;
    }

    std::string Competition::getName() const {
        return name_;
    }
}