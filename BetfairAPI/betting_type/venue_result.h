#pragma once

#include <string>

namespace BetfairAPI::BettingType {
    class VenueResult {
        public:
            VenueResult(std::string venue, int market_count);
            ~VenueResult() = default;
            VenueResult(const VenueResult&) = default;
            VenueResult(VenueResult&&) noexcept = default;
            VenueResult& operator=(const VenueResult&) = default;
            VenueResult& operator=(VenueResult&&) noexcept = default;
        
        const std::string& getVenue() const;
        int getMarketCount() const;

        private:
            std::string venue_;
            int market_count_;
    };
}