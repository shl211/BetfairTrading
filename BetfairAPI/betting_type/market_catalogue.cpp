#include "market_catalogue.h"

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

    const std::string& MarketCatalogue::market_id() const {
        return market_id_;
    }

    const std::string& MarketCatalogue::market_name() const {
        return market_name_;
    }

    const BetfairAPI::Utils::Date& MarketCatalogue::market_start_time() const {
        return market_start_time_;
    }

    const MarketDescription& MarketCatalogue::description() const {
        return description_;
    }

    double MarketCatalogue::total_matched() const {
        return total_matched_;
    }

    const std::vector<RunnerCatalog>& MarketCatalogue::runners() const {
        return runners_;
    }

    const EventType& MarketCatalogue::event_type() const {
        return event_type_;
    }

    const Competition& MarketCatalogue::competition() const {
        return competition_;
    }

    const Event& MarketCatalogue::event() const {
        return event_;
    }

}