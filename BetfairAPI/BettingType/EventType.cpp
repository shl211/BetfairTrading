#include "EventType.h"

namespace BetfairAPI::BettingType {
    EventType::EventType(std::string_view id, std::string_view name) 
        : id_(id), name_(name) {}

    std::string EventType::getId() {
        return id_;
    }

    std::string EventType::getName() {
        return name_;
    }
}