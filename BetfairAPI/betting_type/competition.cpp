#include "competition.h"

namespace BetfairAPI::BettingType {
    Competition::Competition(std::string_view id, std::string_view name) 
        : id_(id), name_(name) {};

    std::string Competition::getId() const {
        return id_;
    }

    std::string Competition::getName() const {
        return name_;
    }
}