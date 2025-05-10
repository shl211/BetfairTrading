#include "MarketFilter.h"

namespace BetfairAPI {
    MarketFilter::MarketFilter() {
        //do nothing
    }

    MarketFilter::~MarketFilter() {
        //do nothing
    }

    nlohmann::json MarketFilter::getFilterJson() const {
        nlohmann::json j = {{"",""}}; //initialise with empty json

        if (includeInPlayOnly) {
            j["inPlayOnly"] = inPlayOnly;
        }

        return j;
    }


    void MarketFilter::setInPlay(bool inPlayOnly) {
        includeInPlayOnly = true;
        this->inPlayOnly = inPlayOnly;
    }
}