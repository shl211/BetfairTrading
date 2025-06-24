#pragma once

#include <string>
#include <chrono>

/*
TODO: Implement more robuse Date class. For now, this is a placeholder to allow progress elsewhere. 
*/
namespace BetfairAPI::Utils {

    class Date {
        public:
            explicit Date(std::string_view iso8601);
            Date() = default;
            ~Date() = default;
            Date(const Date& other) = default;
            Date(Date&& other) noexcept = default;
            Date& operator=(const Date& other) = default;
            Date& operator=(Date&& other) noexcept = default;

            bool operator==(const Date& other) const;
            bool operator!=(const Date& other) const;
            
            friend std::ostream& operator<<(std::ostream& os, const Date& date);

            std::string toIsoString() const;

        private:
            std::string zoned_time_;
    };

}