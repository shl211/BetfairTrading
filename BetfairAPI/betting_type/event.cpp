#include "event.h"
#include <ostream>

namespace BetfairAPI::BettingType {
    Event::Event(std::string_view id,std::string_view name,std::string_view country_code,
                std::string_view timezone,std::string_view venue,BetfairAPI::Utils::Date open_date)
        : id_(id),name_(name),country_code_(country_code),timezone_(timezone),
            venue_(venue),open_date_(std::move(open_date)) {}

    bool Event::operator==(const Event& other) const {
        return id_ == other.id_;
    }

    bool Event::operator!=(const Event& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        os << "Event{id: " << event.id_
            << ", name: " << event.name_
            << ", country_code: " << event.country_code_
            << ", timezone: " << event.timezone_
            << ", venue: " << event.venue_
            << ", open_date: " << event.open_date_
            << "}";
        return os;
    }

    std::string Event::getId() const {
        return id_;
    }

    std::string Event::getName() const {
        return name_;
    }

    std::string Event::getCountryCode() const {
        return country_code_;
    }

    std::string Event::getTimezone() const {
        return timezone_;
    }

    std::string Event::getVenue() const {
        return venue_;
    }

    BetfairAPI::Utils::Date Event::getDate() const {
        return open_date_;
    }
}