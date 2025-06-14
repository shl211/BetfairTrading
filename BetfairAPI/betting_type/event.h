#pragma once

#include <string>
#include "utils/date_utils.h"

namespace BetfairAPI::BettingType {
    class Event {
        public:
            Event(std::string_view id,std::string_view name,std::string_view country_code,
                std::string_view timezone,std::string_view venue,BetfairAPI::Utils::Date open_date);
            ~Event() = default;
            Event(const Event&) = default;
            Event(Event&&) noexcept = default;
            Event& operator=(const Event&) = default;
            Event& operator=(Event&&) noexcept = default;

            std::string getId() const;
            std::string getName() const;
            std::string getCountryCode() const;
            std::string getTimezone() const;
            std::string getVenue() const;
            BetfairAPI::Utils::Date getDate() const;

        private:
            std::string id_;
            std::string name_;
            std::string country_code_;
            std::string timezone_;
            std::string venue_;
            BetfairAPI::Utils::Date open_date_;
    };
}