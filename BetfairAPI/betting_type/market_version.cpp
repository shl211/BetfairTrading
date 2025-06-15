#include "market_version.h"

namespace BetfairAPI::BettingType {

    MarketVersion::MarketVersion(long version)
        : version_(version) {}

    long MarketVersion::getVersion() {
        return version_;
    }
}
