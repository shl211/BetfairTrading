#include "EventType.h"

namespace BetfairAPI::BettingType {
    EventType::EventType(std::string_view id, std::string_view name) 
        : id_(id), name_(name) {}

    bool EventType::operator==(const EventType& other) const {
        return id_ == other.id_;
    }

    bool EventType::operator!=(const EventType& other) const {
        return !(*this == other);
    }
    
    std::string EventType::getId() const {
        return id_;
    }

    std::string EventType::getName() const {
        return name_;
    }
}