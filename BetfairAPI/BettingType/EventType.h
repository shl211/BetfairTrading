#pragma once
#include <string>

namespace BetfairAPI::BettingType {
    class EventType {
        public:
            EventType(std::string_view id, std::string_view name);
            ~EventType()=default;
            //compiler defaults for copy and move semantics should be ok
            //as members also have those semantics implemented
            bool operator==(const EventType& other) const;
            bool operator!=(const EventType& other) const;

            std::string getId() const;
            std::string getName() const;

        private:
            std::string id_;
            std::string name_;
    };
}