#include "venue_result.h"

namespace BetfairAPI::BettingType {

    VenueResult::VenueResult(std::string venue, int market_count)
        : venue_(std::move(venue)), market_count_(market_count) {}

    const std::string& VenueResult::getVenue() const {
        return venue_;
    }

    int VenueResult::getMarketCount() const {
        return market_count_;
    }

}