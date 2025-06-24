#include "event_type.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    EventType::EventType(std::string_view id, std::string_view name) 
        : id_(id), name_(name) {}

    bool EventType::operator==(const EventType& other) const {
        return id_ == other.id_;
    }

    bool EventType::operator!=(const EventType& other) const {
        return !(*this == other);
    }
    
    std::ostream& operator<<(std::ostream& os, const EventType& eventType) {
        os << "EventType{id: " << eventType.id_ << ", name: " << eventType.name_ << "}";
        return os;
    }
            

    std::string EventType::getId() const {
        return id_;
    }

    std::string EventType::getName() const {
        return name_;
    }
}