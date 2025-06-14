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
            ~Date() = default;

            std::string toIsoString() const;

        private:
            std::string zoned_time_;
    };

}