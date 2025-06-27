#include "market_version.h"

namespace BetfairAPI::BettingType {

    MarketVersion::MarketVersion(long version)
        : version_(version) {}


    bool MarketVersion::operator==(const MarketVersion& other) const {
        return version_ == other.version_;
    }

    bool MarketVersion::operator!=(const MarketVersion& other) const {
        return !(*this == other);
    }

    long MarketVersion::getVersion() const {
        return version_;
    }
}
