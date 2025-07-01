#include "betfair_manager.h"

#include <cstring>
#include <atomic>
#include <iostream>
#include "login_api.h"
#include "betting_api.h"
#include "account_api.h"
#include "utils/response.h"
#include "betting_type_json_serialiser.h"

namespace BetfairAPI {
    BetfairManager::~BetfairManager() {
        // Clear application_token
        if (!application_token_.empty()) {
            volatile char* p = &application_token_[0];
            std::memset(const_cast<char*>(p), 0, application_token_.size());
            std::atomic_thread_fence(std::memory_order_release);
            application_token_.clear();
        }
        // Clear session_token
        if (!session_token_.empty()) {
            volatile char* p = &session_token_[0];
            std::memset(const_cast<char*>(p), 0, session_token_.size());
            std::atomic_thread_fence(std::memory_order_release);
            session_token_.clear();
        }
    }
    
    BetfairManager::BetfairManager(std::string username, std::string password, std::string api_key) :
        application_token_(std::string(api_key)) {
        
        //get login and session information
        BetfairAPI::Utils::Response r = login(application_token_,username,password);
        auto login_info = r.get_data();
        session_token_ = login_info["token"];
    
        //initialise with account information
        r = getAccountFunds(application_token_,session_token_);
        auto account_info = r.get_data();
        assignAccountInformation(account_info);
    };
    
    BetfairManager::BetfairManager(BetfairManager&& other) noexcept : 
        balance_(std::move(other.balance_)),
        discount_rate_(std::move(other.discount_rate_)),
        exposure_(std::move(other.exposure_)),
        exposure_limit_(std::move(other.exposure_limit_)),
        session_token_(std::move(other.session_token_)),
        application_token_(std::move(other.application_token_)) {
            //reset states in other
            other.balance_ = 0.0;
            other.discount_rate_ = 0.0;
            other.exposure_ = 0.0;
            other.exposure_limit_ = 0.0;

            //strings are automatically empty after std::move
    };

    BetfairManager& BetfairManager::operator=(BetfairManager&& other) noexcept {
        if(this != &other) {
            balance_ = std::move(other.balance_);
            discount_rate_ = std::move(other.discount_rate_);
            exposure_ = std::move(other.exposure_);
            exposure_limit_ = std::move(other.exposure_limit_);
            session_token_ = std::move(other.session_token_);
            application_token_ = std::move(other.application_token_);

            // Reset other state
            other.balance_ = 0.0;
            other.discount_rate_ = 0.0;
            other.exposure_ = 0.0;
            other.exposure_limit_ = 0.0;
            // Strings are automatically empty after std::move
        }

        return *this;
    }

    double BetfairManager::getAccountBalance() const {
        return balance_;
    }

    std::vector<BettingType::EventTypeResults> BetfairManager::listEventTypes(const BettingType::MarketFilter& mf,const std::string& locale) const {
        auto r = BetfairAPI::listEventTypes(application_token_,session_token_,mf,locale);
        
        std::vector<BetfairAPI::BettingType::EventTypeResults> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::EventTypeResults>());
        }
        
        return res;
    }

    std::vector<BettingType::CompetitionResult> BetfairManager::listCompetitions(const BettingType::MarketFilter& mf,const std::string& locale) const {
        auto r = BetfairAPI::listCompetitions(application_token_,session_token_,mf,locale);
        
        std::vector<BetfairAPI::BettingType::CompetitionResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::CompetitionResult>());
        }
        
        return res;
    }
    
    std::vector<BettingType::EventResult> BetfairManager::listEvents(const BettingType::MarketFilter& mf,const std::string& locale) const {
        auto r = BetfairAPI::listEvents(application_token_,session_token_,mf,locale);

        std::vector<BetfairAPI::BettingType::EventResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::EventResult>());
        }
        
        return res;
    }
    
    std::vector<BettingType::MarketTypeResult> BetfairManager::listMarketTypes(const BettingType::MarketFilter& mf, const std::string& locale) const {
        auto r = BetfairAPI::listMarketTypes(application_token_,session_token_,mf,locale);
        
        std::vector<BetfairAPI::BettingType::MarketTypeResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::MarketTypeResult>());
        }
        
        return res;
    }
    
    std::vector<BettingType::TimeRangeResult> BetfairManager::listTimeRanges(const BettingType::MarketFilter& mf, BettingEnum::TimeGranularity granularity) const {
        auto r = BetfairAPI::listTimeRanges(application_token_,session_token_,mf,granularity);
        
        std::vector<BetfairAPI::BettingType::TimeRangeResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::TimeRangeResult>());
        }
        
        return res;
    }
    
    std::vector<BettingType::CountryCodeResult> BetfairManager::listCountries(const BettingType::MarketFilter& mf, const std::string& locale) const {
        auto r = BetfairAPI::listCountries(application_token_,session_token_,mf,locale);
        
        std::vector<BetfairAPI::BettingType::CountryCodeResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::CountryCodeResult>());
        }
        
        return res;
    }
    
    std::vector<BettingType::VenueResult> BetfairManager::listVenues(const BettingType::MarketFilter& mf, const std::string& locale) const {
        auto r = BetfairAPI::listVenues(application_token_,session_token_,mf,locale);
        
        std::vector<BetfairAPI::BettingType::VenueResult> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::VenueResult>());
        }
        
        return res;
    }

    std::vector<BettingType::MarketCatalogue> BetfairManager::listMarketCatalogue(const BettingType::MarketFilter& filter, 
        const std::vector<BettingEnum::MarketProjection>& market_projection, BettingEnum::MarketSort sort,         
        int max_results, const std::string& locale) {

        auto r = BetfairAPI::listMarketCatalogue(application_token_,session_token_,filter,market_projection,sort,max_results,locale);
        
        std::vector<BetfairAPI::BettingType::MarketCatalogue> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::MarketCatalogue>());
        }
        
        return res;
    }

    std::vector<BettingType::MarketBook> BetfairManager::listMarketBook(
        const std::vector<std::string>& market_ids, BettingEnum::OrderProjection order_projection,
        BettingEnum::MatchProjection match_projection, bool include_overall_position,
        bool position_matched_by_strategy_ref, const std::vector<std::string>& customer_strategy_refs,
        const std::string& currency_code, const std::string& locale, 
        const Utils::Date& matched_since,const std::vector<std::string>& bet_id) {

        auto r = BetfairAPI::listMarketBook(
            application_token_,
            session_token_,
            market_ids,
            order_projection,
            match_projection,
            include_overall_position,
            position_matched_by_strategy_ref,
            customer_strategy_refs,
            currency_code,
            locale,
            matched_since,
            bet_id
        );

        std::vector<BetfairAPI::BettingType::MarketBook> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::MarketBook>());
        }
        
        return res;

    }

    std::vector<BettingType::MarketBook> BetfairManager::listMarketBook(
        const std::vector<std::string>& market_ids, const BettingType::PriceProjection& price_projection,
        BettingEnum::OrderProjection order_projection,BettingEnum::MatchProjection match_projection,
        bool include_overall_position,bool position_matched_by_strategy_ref,
        std::vector<std::string> customer_strategy_refs,std::string currency_code,
        std::string locale, Utils::Date matched_since,std::vector<std::string> bet_id) {

        auto r = BetfairAPI::listMarketBook(
            application_token_,
            session_token_,
            market_ids,
            price_projection,
            order_projection,
            match_projection,
            include_overall_position,
            position_matched_by_strategy_ref,
            customer_strategy_refs,
            currency_code,
            locale,
            matched_since,
            bet_id
        );
        
        std::vector<BetfairAPI::BettingType::MarketBook> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::MarketBook>());
        }
        
        return res;

    }

    std::vector<BettingType::MarketProfitLoss> BetfairManager::listMarketProfitAndLoss(const std::vector<std::string>& market_ids,
        bool include_settled_bets,bool include_bsp_bets,bool net_of_commission) {

        auto r = BetfairAPI::listMarketProfitAndLoss(application_token_,session_token_,market_ids,
            include_settled_bets,include_bsp_bets,net_of_commission);
        
        std::vector<BetfairAPI::BettingType::MarketProfitLoss> res;
        res.reserve(r.get_data().size());
        for(auto& i : r.get_data()) {
            res.push_back(i.get<BetfairAPI::BettingType::MarketProfitLoss>());
        }
        
        return res;
    }

    BettingType::CurrentOrderSummaryReport BetfairManager::listCurrentOrders(
        const std::vector<std::string>& bet_ids, 
        const std::vector<std::string>& market_ids,
        const BettingType::TimeRange& placed_date_range,
        BettingEnum::OrderProjection order_projection,
        BettingEnum::OrderBy order_by,
        BettingEnum::SortDir sort_dir,
        int from_record,
        int record_count,
        bool include_item_desc,
        bool include_source_id,
        const std::vector<std::string>& customer_order_refs,
        const std::vector<std::string>& customer_strategy_ref
    ) {
        auto r = BetfairAPI::listCurrentOrders(
            application_token_,
            session_token_,
            bet_ids,
            market_ids,
            order_projection,
            placed_date_range,
            order_by,
            sort_dir,
            from_record,
            record_count,
            include_item_desc,
            include_source_id,
            customer_order_refs,
            customer_strategy_ref
        );

        return r.get_data().get<BettingType::CurrentOrderSummaryReport>();
    }

    BettingType::ClearedOrderSummaryReport BetfairManager::listClearedOrders (
        BettingEnum::BetStatus bet_status,
        const std::vector<BettingType::EventType>& event_types,
        const std::vector<BettingType::Event>& events,
        const std::vector<BettingType::MarketTypeResult>& market_types,
        const std::vector<BettingType::Runner>& runners,
        const std::vector<std::string>& bet_ids,
        BettingEnum::Side side,
        const BettingType::TimeRange& settled_date_range,
        BettingEnum::GroupBy group_by,
        int from_record,
        int record_count, 
        bool include_item_desc,
        bool include_source_id,
        const std::vector<std::string>& customer_order_refs,
        const std::vector<std::string>& customer_strategy_ref,
        const std::string& locale
    ) {
        std::vector<std::string> e_type_id;
        std::vector<std::string> e_id;
        std::vector<std::string> m_id;
        std::vector<long> r_id;

        e_type_id.reserve(event_types.size());
        for(auto& et : event_types) {
            e_type_id.push_back(et.getId());
        }

        e_id.reserve(events.size());
        for(auto& e : events) {
            e_id.push_back(e.getId());
        }

        m_id.reserve(market_types.size());
        for(auto& m : market_types) {
            m_id.push_back(m.getMarketType());
        }

        r_id.reserve(runners.size());
        for(auto& r : runners) {
            r_id.push_back(r.getSelectionId());
        }

        std::cout << "H\n";
        auto r = BetfairAPI::listClearedOrders(
            application_token_,
            session_token_,
            bet_status,
            e_type_id,
            e_id,
            m_id,
            r_id,
            bet_ids,
            side,
            settled_date_range,
            group_by,
            include_item_desc,
            include_source_id,
            locale,
            from_record,
            record_count,
            customer_order_refs,
            customer_strategy_ref
        );
        return r.get_data().get<BettingType::ClearedOrderSummaryReport>();
    }


    /******************************************************************************
    * PRIVATE
    ******************************************************************************/
    
    void BetfairManager::assignAccountInformation(const nlohmann::json& account_balance_response) {
        balance_ = account_balance_response["availableToBetBalance"];
        discount_rate_ = account_balance_response["discountRate"];
        exposure_ = account_balance_response["exposure"];
        exposure_limit_ = account_balance_response["exposureLimit"];
    }
}