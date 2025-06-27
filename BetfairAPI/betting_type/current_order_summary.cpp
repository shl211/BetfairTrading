#include "current_order_summary.h"
#include <ostream>
#include "utils/enum_utils.hpp"

namespace BetfairAPI::BettingType {
    CurrentOrderSummary::CurrentOrderSummary(std::string_view bet_id,std::string_view market_id,long selection_id,
        double handicap,PriceSize price_size,double bsp_liability,BetfairAPI::BettingEnum::Side side,
        BetfairAPI::BettingEnum::OrderStatus status,BetfairAPI::BettingEnum::PersistenceType persistence_type,
        BetfairAPI::BettingEnum::OrderType order_type, BetfairAPI::Utils::Date placed_date,
        BetfairAPI::Utils::Date matched_date)
        : bet_id_(std::string(bet_id)), market_id_(std::string(market_id)), selection_id_(selection_id),
            handicap_(handicap), price_size_(std::move(price_size)),bsp_liability_(bsp_liability),
            side_(side),status_(status),persistence_type_(persistence_type),order_type_(order_type),
            placed_date_(std::move(placed_date)),matched_date_(std::move(matched_date)) {}

    std::ostream& operator<<(std::ostream& os, const CurrentOrderSummary& summary) {
        //what else is needed here?
        os << Utils::to_string<BettingEnum::Side>(summary.side_) <<  " Bet: " << 
            summary.bet_id_ << ", Market: " << summary.market_id_ <<
            ", Selection: " << summary.selection_id_ << 
            ", Price-Size: p" << summary.price_size_.getPrice() << "-s" << summary.price_size_.getSize() <<
            ", status: " << Utils::to_string<BettingEnum::OrderStatus>(summary.status_);
            
        return os;
    }


    void CurrentOrderSummary::setAveragePriceMatched(double val) {
        average_price_matched_ = val;
    }

    void CurrentOrderSummary::setSizeMatched(double val) {
        size_matched_ = val;
    }

    void CurrentOrderSummary::setSizeRemaining(double val) {
        size_remaining_ = val;
    }

    void CurrentOrderSummary::setSizeLapsed(double val) {
        size_lapsed_ = val;
    }

    void CurrentOrderSummary::setSizeCancelled(double val) {
        size_cancelled_ = val;
    }

    void CurrentOrderSummary::setSizeVoided(double val) {
        size_voided_ = val;
    }

    void CurrentOrderSummary::setRegulatorAuthCode(std::string_view s) {
        regulator_auth_code_ = std::string(s);
    }

    void CurrentOrderSummary::setRegulatorCode(std::string_view s) {
        regulator_code_ = std::string(s);
    }

    void CurrentOrderSummary::setCustomerOrderRef(std::string_view s) {
        customer_order_ref_ = std::string(s);
    }

    void CurrentOrderSummary::setCustomerStrategyRef(std::string_view s) {
        customer_strategy_ref_ = std::string(s);
    }    

    void CurrentOrderSummary::setCurrentItemDescription(CurrentItemDescription item) {
        current_item_description_ = std::move(item);
    }

    void CurrentOrderSummary::setSourceIdKey(std::string_view s) {
        source_id_key_ = std::string(s);
    }

    void CurrentOrderSummary::setSourceIdDescription(std::string_view s) {
        source_id_description_ = std::string(s);
    }

    const std::string& CurrentOrderSummary::getBetId() const {
        return bet_id_;
    }

    const std::string& CurrentOrderSummary::getMarketId() const {
        return market_id_;
    }

    long CurrentOrderSummary::getSelectionId() const {
        return selection_id_;
    }

    double CurrentOrderSummary::getHandicap() const {
        return handicap_;
    }

    const PriceSize& CurrentOrderSummary::getPriceSize() const {
        return price_size_;
    }

    double CurrentOrderSummary::getBspLiability() const {
        return bsp_liability_;
    }

    BetfairAPI::BettingEnum::Side CurrentOrderSummary::getSide() const {
        return side_;
    }

    BetfairAPI::BettingEnum::OrderStatus CurrentOrderSummary::getStatus() const {
        return status_;
    }

    BetfairAPI::BettingEnum::PersistenceType CurrentOrderSummary::getPersistenceType() const {
        return persistence_type_;
    }

    BetfairAPI::BettingEnum::OrderType CurrentOrderSummary::getOrderType() const {
        return order_type_;
    }

    const BetfairAPI::Utils::Date& CurrentOrderSummary::getPlacedDate() const {
        return placed_date_;
    }

    const BetfairAPI::Utils::Date& CurrentOrderSummary::getMatchedDate() const {
        return matched_date_;
    }

    double CurrentOrderSummary::getAveragePriceMatched() const {
        return average_price_matched_;
    }

    double CurrentOrderSummary::getSizeMatched() const {
        return size_matched_;
    }

    double CurrentOrderSummary::getSizeRemaining() const {
        return size_remaining_;
    }

    double CurrentOrderSummary::getSizeLapsed() const {
        return size_lapsed_;
    }

    double CurrentOrderSummary::getSizeCancelled() const {
        return size_cancelled_;
    }

    double CurrentOrderSummary::getSizeVoided() const {
        return size_voided_;
    }

    const std::string& CurrentOrderSummary::getRegulatorAuthCode() const {
        return regulator_auth_code_;
    }

    const std::string& CurrentOrderSummary::getRegulatorCode() const {
        return regulator_code_;
    }

    const std::string& CurrentOrderSummary::getCustomerOrderRef() const {
        return customer_order_ref_;
    }

    const std::string& CurrentOrderSummary::getCustomerStrategyRef() const {
        return customer_strategy_ref_;
    }

    const CurrentItemDescription& CurrentOrderSummary::getCurrentItemDescription() const {
        return current_item_description_;
    }

    const std::string& CurrentOrderSummary::getSourceIdKey() const {
        return source_id_key_;
    }

    const std::string& CurrentOrderSummary::getSourceIdDescription() const {
        return source_id_description_;
    }



}