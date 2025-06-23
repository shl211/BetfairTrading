#include "runner.h"

namespace BetfairAPI::BettingType {
    Runner::Runner(long selection_id,double handicap, BetfairAPI::BettingEnum::RunnerStatus status) 
        : selection_id_(selection_id), handicap_(handicap), status_(status) {}



    void Runner::setAdjustmentFactor(double val) {
        adjustment_factor_ = val;
    }

    void Runner::setLastPriceTraded(double val) {
        last_price_traded_ = val;
    }

    void Runner::setTotalMatched(double val) {
        total_matched_ = val;
    }
    
    void Runner::setRemovalDate(BetfairAPI::Utils::Date date) {
        removal_date_ = std::move(date);
    }

    void Runner::setStartingPrices(StartingPrices sp) {
        sp_ = std::move(sp);
    }

    void Runner::setExchangePrices(ExchangePrices ex) {
        ex_ = std::move(ex);
    }

    void Runner::addOrder(Order order) {
        orders_.push_back(std::move(order));
    }

    void Runner::addMatch(Match match) {
        matches_.push_back(std::move(match));
    }

    void Runner::addMatchByStrategy(const std::string& strategy, Match match) {
        matches_by_strategy_.insert({strategy,std::move(match)});
    }

    long Runner::getSelectionId() const {
        return selection_id_;
    }

    double Runner::getHandicap() const {
        return handicap_;
    }

    BetfairAPI::BettingEnum::RunnerStatus Runner::getStatus() const {
        return status_;
    }

    double Runner::getAdjustmentFactor() const {
        return adjustment_factor_;
    }

    double Runner::getLastPriceTraded() const {
        return last_price_traded_;
    }

    double Runner::getTotalMatched() const {
        return total_matched_;
    }

    BetfairAPI::Utils::Date Runner::getRemovalDate() const {
        return removal_date_;
    }

    const StartingPrices& Runner::getStartingPrices() const {
        return sp_;
    }

    const ExchangePrices& Runner::getExchangePrices() const {
        return ex_;
    }

    const std::vector<Order>& Runner::getOrders() const {
        return orders_;
    }

    const std::vector<Match>& Runner::getMatches() const {
        return matches_;
    }

    const std::map<std::string, Match>& Runner::getMatchesByStrategy() const {
        return matches_by_strategy_;
    }
}