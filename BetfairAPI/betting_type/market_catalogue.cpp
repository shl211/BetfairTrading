#include "market_catalogue.h"
#include <ostream>

namespace BetfairAPI::BettingType {

MarketCatalogue::MarketCatalogue(std::string market_id, std::string market_name,
    BetfairAPI::Utils::Date market_start_time, MarketDescription description,
    double total_matched, std::vector<RunnerCatalog> runners,
    EventType event_type, Competition competition, Event event)
    : market_id_(std::move(market_id)),
        market_name_(std::move(market_name)),
        market_start_time_(std::move(market_start_time)),
        description_(std::move(description)),
        total_matched_(total_matched),
        runners_(std::move(runners)),
        event_type_(std::move(event_type)),
        competition_(std::move(competition)),
        event_(std::move(event)) {}

    std::ostream& operator<<(std::ostream& os, const MarketCatalogue& mc) {
        /**********************************************************************
        still work in progress
        **********************************************************************/
        os << "MarketCatalogue { "
            << "market_id: " << mc.market_id_
            << ", market_name: " << mc.market_name_;

        if (mc.total_matched_ != 0.0) {
            os << ", total_matched: " << mc.total_matched_;
        }

        if (!mc.competition_.getId().empty()) {
            os << ", competition: " << mc.competition_.getName();
        }

        if (!mc.event_.getId().empty()) {
            os << ", event: " << mc.event_.getName();
        }

        if (!mc.event_type_.getId().empty()) {
            os << ", event type: " << mc.event_type_.getName();
        }

        //os << " TODO: description, runners, market start time";
        return os;
    }


    const std::string& MarketCatalogue::getMarketId() const {
        return market_id_;
    }

    const std::string& MarketCatalogue::getMarketName() const {
        return market_name_;
    }

    const BetfairAPI::Utils::Date& MarketCatalogue::getMarketStartTime() const {
        return market_start_time_;
    }

    const MarketDescription& MarketCatalogue::getDescription() const {
        return description_;
    }

    double MarketCatalogue::getTotalMatched() const {
        return total_matched_;
    }

    const std::vector<RunnerCatalog>& MarketCatalogue::getRunners() const {
        return runners_;
    }

    const EventType& MarketCatalogue::getEventType() const {
        return event_type_;
    }

    const Competition& MarketCatalogue::getCompetition() const {
        return competition_;
    }

    const Event& MarketCatalogue::getEvent() const {
        return event_;
    }

}