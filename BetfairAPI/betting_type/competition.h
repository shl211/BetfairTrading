#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class Competition {
        public:
            Competition(std::string_view id, std::string_view name);
            Competition() = default;
            ~Competition() = default;
            Competition(const Competition&) = default;
            Competition(Competition&&) noexcept = default;
            Competition& operator=(const Competition&) = default;
            Competition& operator=(Competition&&) noexcept = default;

            bool operator==(const Competition& other) const;
            bool operator!=(const Competition& other) const;
            friend std::ostream& operator<<(std::ostream& os, const Competition& competition);
            
            std::string getId() const;
            std::string getName() const;

        private:
            std::string id_;
            std::string name_;
    };
}
