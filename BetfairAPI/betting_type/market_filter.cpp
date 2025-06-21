#include "market_filter.h"

namespace BetfairAPI::BettingType {
    void MarketFilter::setQuery(std::string_view text_query) {
        text_query_ = text_query;
    }

    void MarketFilter::addEventTypeId(std::string_view event_type_id) {
        event_type_ids_.push_back(std::string(event_type_id));
    }

    void MarketFilter::addEventId(std::string_view event_id) {
        event_ids_.push_back(std::string(event_id));
    }

    void MarketFilter::addCompetitionId(std::string_view competition_id) {
        competition_ids_.push_back(std::string(competition_id));
    }

    void MarketFilter::addMarketId(std::string_view market_id) {
        market_ids_.push_back(std::string(market_id));
    }

    void MarketFilter::addVenue(std::string_view venue) {
        venues_ids_.push_back(std::string(venue));
    }

    void MarketFilter::setBspOnly(bool bsp_only) {
        bsp_only_ = bsp_only;
    }

    void MarketFilter::setTurnInPlayEnabled(bool turn_in_play_enabled) {
        turn_in_play_enabled_ = turn_in_play_enabled;
    }

    void MarketFilter::setInPlayOnly(bool in_play_only) {
        in_play_only_ = in_play_only;
    }

    void MarketFilter::addMarketBettingType(BetfairAPI::BettingEnum::MarketBettingType market_betting_type) {
        market_betting_types_.push_back(market_betting_type);
    }

    void MarketFilter::addMarketCountry(std::string_view market_country) {
        market_countries_.push_back(std::string(market_country));
    }

    void MarketFilter::addMarketTypeCode(std::string_view market_type_code) {
        market_type_codes_.push_back(std::string(market_type_code));
    }

    void MarketFilter::setMarketStartTime(TimeRange time_range) {
        market_start_time_ = time_range;
    }

    void MarketFilter::addOrder(BetfairAPI::BettingEnum::OrderStatus order) {
        with_orders_.push_back(order);
    }

    void MarketFilter::addRaceType(std::string_view race_type) {
        race_types_.push_back(std::string(race_type));
    }

    std::string MarketFilter::getQuery() const {
        return text_query_;
    }

    const std::vector<std::string>& MarketFilter::getEventTypeIds() const {
        return event_type_ids_;
    }

    const std::vector<std::string>& MarketFilter::getEventIds() const {
        return event_ids_;
    }

    const std::vector<std::string>& MarketFilter::getCompetitionIds() const {
        return competition_ids_;
    }

    const std::vector<std::string>& MarketFilter::getMarketIds() const {
        return market_ids_;
    }

    const std::vector<std::string>& MarketFilter::getVenues() const {
        return venues_ids_;
    }

    bool MarketFilter::isBspOnly() const {
        return bsp_only_;
    }

    bool MarketFilter::isTurnInPlayEnabled() const {
        return turn_in_play_enabled_;
    }

    bool MarketFilter::isInPlayOnly() const {
        return in_play_only_;
    }

    const std::vector<BetfairAPI::BettingEnum::MarketBettingType>& MarketFilter::getMarketBettingTypes() const {
        return market_betting_types_;
    }

    const std::vector<std::string>& MarketFilter::getMarketCountries() const {
        return market_countries_;
    }

    const std::vector<std::string>& MarketFilter::getMarketTypeCodes() const {
        return market_type_codes_;
    }

    const TimeRange& MarketFilter::getMarketStartTime() const {
        return market_start_time_;
    }

    const std::vector<BetfairAPI::BettingEnum::OrderStatus>& MarketFilter::getOrders() const {
        return with_orders_;
    }

    const std::vector<std::string>& MarketFilter::getRaceTypes() const {
        return race_types_;
    }
}