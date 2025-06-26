#include "market_book.h"
#include "utils/enum_utils.hpp"
#include <ostream>

namespace BetfairAPI::BettingType {

    MarketBook::MarketBook(const std::string& market_id,bool is_market_delayed)
        : market_id_(market_id), is_market_data_delayed_(is_market_delayed) {}

    std::ostream& operator<<(std::ostream& os, const MarketBook& market_book) {
        os << "MarketBook for Market{" << market_book.market_id_ 
            << "} and isMarketDataDelayed{" << market_book.isMarketDataDelayed() << "} ";
            
        if(market_book.status_ != BettingEnum::MarketStatus::UNKNOWN) {
            os << " MarketStatus{" << Utils::to_string<BettingEnum::MarketStatus>(market_book.status_) << "}";
        }

        os << ". More information available by querying relevant get functions. ";
        return os;
    }



    void MarketBook::setStatus(BetfairAPI::BettingEnum::MarketStatus status) {
        status_ = status;
    }
    
    void MarketBook::setBetDelay(bool is_bet_delay) {
        bet_delay_ = is_bet_delay; 
    }

    void MarketBook::setBspReconciled(bool is_bsp_reconciled) {
        bsp_reconciled_ = is_bsp_reconciled;
    }

    void MarketBook::setComplete(bool is_complete) {
        complete_ = is_complete;
    }

    void MarketBook::setInplay(bool is_inplay) {
        inplay_ = is_inplay;
    }
    
    void MarketBook::setNumberOfWinners(int n) {
        number_of_winners_ = n;
    }
    
    void MarketBook::setNumberOfRunners(int n) {
        number_of_runners_ = n;
    }

    void MarketBook::setNumberOfActiveRunners(int n) {
        number_of_active_runners_ = n;
    }

    void MarketBook::setLastMatchTime(BetfairAPI::Utils::Date date) {
        last_match_time_ = std::move(date);
    }

    void MarketBook::setTotalMatched(double val) {
        total_matched_ = val;
    }

    void MarketBook::setTotalAvailable(double val) {
        total_available_ = val;
    }

    void MarketBook::setCrossMatching(bool is_cross_matching) {
        cross_matching_ = is_cross_matching;
    }

    void MarketBook::setRunnersVoidable(bool is_runners_voidable) {
        runners_voidable_ = is_runners_voidable;
    }

    void MarketBook::setVersion(long version) {
        version_ = version;
    }

    void MarketBook::addRunners(Runner runner) {
        runners_.push_back(std::move(runner));
    }

    void MarketBook::setKeyLineDescription(KeyLineDescription k) {
        key_line_description_ = std::move(k);
    }

    const std::string& MarketBook::getMarketId() const {
        return market_id_;
    }

    bool MarketBook::isMarketDataDelayed() const {
        return is_market_data_delayed_;
    }

    BetfairAPI::BettingEnum::MarketStatus MarketBook::getStatus() const {
        return status_;
    }

    int MarketBook::getBetDelay() const {
        return bet_delay_;
    }

    bool MarketBook::isBspReconciled() const {
        return bsp_reconciled_;
    }

    bool MarketBook::isComplete() const {
        return complete_;
    }

    bool MarketBook::isInplay() const {
        return inplay_;
    }

    int MarketBook::getNumberOfWinners() const {
        return number_of_winners_;
    }

    int MarketBook::getNumberOfRunners() const {
        return number_of_runners_;
    }

    int MarketBook::getNumberOfActiveRunners() const {
        return number_of_active_runners_;
    }

    const BetfairAPI::Utils::Date& MarketBook::getLastMatchTime() const {
        return last_match_time_;
    }

    double MarketBook::getTotalMatched() const {
        return total_matched_;
    }

    double MarketBook::getTotalAvailable() const {
        return total_available_;
    }

    bool MarketBook::isCrossMatching() const {
        return cross_matching_;
    }

    bool MarketBook::isRunnersVoidable() const {
        return runners_voidable_;
    }

    long MarketBook::getVersion() const {
        return version_;
    }

    const std::vector<Runner>& MarketBook::getRunners() const {
        return runners_;
    }

    const KeyLineDescription& MarketBook::getKeyLineDescription() const {
        return key_line_description_;
    }


}