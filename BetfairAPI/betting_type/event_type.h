#pragma once
#include <string>

namespace BetfairAPI::BettingType {
    class EventType {
        public:
            EventType(std::string_view id, std::string_view name);
            EventType()=default;
            ~EventType()=default;
            EventType(const EventType& other) = default;
            EventType(EventType&& other) noexcept = default;
            EventType& operator=(const EventType& other) = default;
            EventType& operator=(EventType&& other) noexcept = default;

            bool operator==(const EventType& other) const;
            bool operator!=(const EventType& other) const;
            friend std::ostream& operator<<(std::ostream& os, const EventType& eventType);
            
            std::string getId() const;
            std::string getName() const;

        private:
            std::string id_;
            std::string name_;
    };
}