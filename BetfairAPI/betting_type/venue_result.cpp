#include "venue_result.h"
#include <ostream>

namespace BetfairAPI::BettingType {

    VenueResult::VenueResult(std::string venue, int market_count)
        : venue_(std::move(venue)), market_count_(market_count) {}

    std::ostream& operator<<(std::ostream& os, const VenueResult& result) {
        os << "VenueResult{venue=\"" << result.venue_ << "\", market_count=" << result.market_count_ << "}";
        return os;
    }

    const std::string& VenueResult::getVenue() const {
        return venue_;
    }

    int VenueResult::getMarketCount() const {
        return market_count_;
    }

}