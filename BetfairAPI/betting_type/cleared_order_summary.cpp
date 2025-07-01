#include <ostream>
#include "cleared_order_summary.h"
#include "utils/enum_utils.hpp"

namespace BetfairAPI::BettingType {
    std::ostream& operator<<(std::ostream& os, const ClearedOrderSummary& summary) {
        os << "event_type_id: " << summary.getEventTypeId()
            << ", event_id: " << summary.getEventId()
            << ", market_id: " << summary.getMarketId()
            << ", selection_id: " << summary.getSelectionId()
            << ", side: " << Utils::to_string<>(summary.getSide())
            << ", profit: " << summary.profit_;
        return os;
    }
    
    // Getters
    const std::string& ClearedOrderSummary::getEventTypeId() const {
        return event_type_id_;
    }
    const std::string& ClearedOrderSummary::getEventId() const {
        return event_id_;
    }
    const std::string& ClearedOrderSummary::getMarketId() const {
        return market_id_;
    }
    long ClearedOrderSummary::getSelectionId() const {
        return selection_id_;
    }
    double ClearedOrderSummary::getHandicap() const {
        return handicap_;
    }
    const std::string& ClearedOrderSummary::getBetId() const {
        return bet_id_;
    }
    const BetfairAPI::Utils::Date& ClearedOrderSummary::getPlacedDate() const {
        return placed_date_;
    }
    BetfairAPI::BettingEnum::PersistenceType ClearedOrderSummary::getPersistenceType() const {
        return persistence_type_;
    }
    BetfairAPI::BettingEnum::OrderType ClearedOrderSummary::getOrderType() const {
        return order_type_;
    }
    BetfairAPI::BettingEnum::Side ClearedOrderSummary::getSide() const {
        return side_;
    }
    const ItemDescription& ClearedOrderSummary::getItemDescription() const {
        return item_description_;
    }
    const std::string& ClearedOrderSummary::getBetOutcome() const {
        return bet_outcome_;
    }
    double ClearedOrderSummary::getPriceRequested() const {
        return price_requested_;
    }
    const BetfairAPI::Utils::Date& ClearedOrderSummary::getSettledDate() const {
        return settled_date_;
    }
    const BetfairAPI::Utils::Date& ClearedOrderSummary::getLastMatchedDate() const {
        return last_matched_date_;
    }
    int ClearedOrderSummary::getBetCount() const {
        return bet_count_;
    }
    double ClearedOrderSummary::getCommission() const {
        return commission_;
    }
    double ClearedOrderSummary::getPriceMatched() const {
        return price_matched_;
    }
    bool ClearedOrderSummary::getPriceReduced() const {
        return price_reduced_;
    }
    double ClearedOrderSummary::getSizeSettled() const {
        return size_settled_;
    }
    double ClearedOrderSummary::getProfit() const {
        return profit_;
    }
    double ClearedOrderSummary::getSizeCancelled() const {
        return size_cancelled_;
    }
    const std::string& ClearedOrderSummary::getCustomerOrderRef() const {
        return customer_order_ref_;
    }
    const std::string& ClearedOrderSummary::getCustomerStrategyRef() const {
        return customer_strategy_ref_;
    }
    const std::string& ClearedOrderSummary::getSourceIdKey() const {
        return source_id_key_;
    }
    const std::string& ClearedOrderSummary::getSourceIdDescription() const {
        return source_id_description_;
    }

    // Setters
    void ClearedOrderSummary::setEventTypeId(const std::string& event_type_id) {
        event_type_id_ = event_type_id;
    }
    void ClearedOrderSummary::setEventId(const std::string& event_id) {
        event_id_ = event_id;
    }
    void ClearedOrderSummary::setMarketId(const std::string& market_id) {
        market_id_ = market_id;
    }
    void ClearedOrderSummary::setSelectionId(long selection_id) {
        selection_id_ = selection_id;
    }
    void ClearedOrderSummary::setHandicap(double handicap) {
        handicap_ = handicap;
    }
    void ClearedOrderSummary::setBetId(const std::string& bet_id) {
        bet_id_ = bet_id;
    }
    void ClearedOrderSummary::setPlacedDate(const BetfairAPI::Utils::Date& placed_date) {
        placed_date_ = placed_date;
    }
    void ClearedOrderSummary::setPersistenceType(BetfairAPI::BettingEnum::PersistenceType persistence_type) {
        persistence_type_ = persistence_type;
    }
    void ClearedOrderSummary::setOrderType(BetfairAPI::BettingEnum::OrderType order_type) {
        order_type_ = order_type;
    }
    void ClearedOrderSummary::setSide(BetfairAPI::BettingEnum::Side side) {
        side_ = side;
    }
    void ClearedOrderSummary::setItemDescription(const ItemDescription& item_description) {
        item_description_ = item_description;
    }
    void ClearedOrderSummary::setBetOutcome(const std::string& bet_outcome) {
        bet_outcome_ = bet_outcome;
    }
    void ClearedOrderSummary::setPriceRequested(double price_requested) {
        price_requested_ = price_requested;
    }
    void ClearedOrderSummary::setSettledDate(const BetfairAPI::Utils::Date& settled_date) {
        settled_date_ = settled_date;
    }
    void ClearedOrderSummary::setLastMatchedDate(const BetfairAPI::Utils::Date& last_matched_date) {
        last_matched_date_ = last_matched_date;
    }
    void ClearedOrderSummary::setBetCount(int bet_count) {
        bet_count_ = bet_count;
    }
    void ClearedOrderSummary::setCommission(double commission) {
        commission_ = commission;
    }
    void ClearedOrderSummary::setPriceMatched(double price_matched) {
        price_matched_ = price_matched;
    }
    void ClearedOrderSummary::setPriceReduced(bool price_reduced) {
        price_reduced_ = price_reduced;
    }
    void ClearedOrderSummary::setSizeSettled(double size_settled) {
        size_settled_ = size_settled;
    }
    void ClearedOrderSummary::setProfit(double profit) {
        profit_ = profit;
    }
    void ClearedOrderSummary::setSizeCancelled(double size_cancelled) {
        size_cancelled_ = size_cancelled;
    }
    void ClearedOrderSummary::setCustomerOrderRef(const std::string& customer_order_ref) {
        customer_order_ref_ = customer_order_ref;
    }
    void ClearedOrderSummary::setCustomerStrategyRef(const std::string& customer_strategy_ref) {
        customer_strategy_ref_ = customer_strategy_ref;
    }
    void ClearedOrderSummary::setSourceIdKey(const std::string& source_id_key) {
        source_id_key_ = source_id_key;
    }
    void ClearedOrderSummary::setSourceIdDescription(const std::string& source_id_description) {
        source_id_description_ = source_id_description;
    }

}