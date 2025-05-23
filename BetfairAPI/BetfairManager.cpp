#include "BetfairManager.h"

#include <cstring>
#include <atomic>
#include <iostream>
#include "LoginAPI.h"
#include "AccountAPI.h"
#include "BettingAPI.h"

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
        Response r = BetfairAPI::login(application_token_,username,password);
        auto login_info = r.get_data();
        session_token_ = login_info["token"];
    
        //initialise with account information
        r = BetfairAPI::getAccountFunds(application_token_,session_token_);
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

    std::vector<EventTypeResult> BetfairManager::listEventTypes(const MarketFilter& filter) {
        Response response = BetfairAPI::listEventTypes(application_token_,session_token_,filter);
        nlohmann::json data = response.get_data();

        std::vector<EventTypeResult> eventList;
        eventList.reserve(data.size());

        for (const auto& item : data) {
            auto event_type = item["eventType"];
            int event_id = std::stoi(event_type["id"].get<std::string>());
            int market_count = item["marketCount"];
            eventList.push_back(EventTypeResult(event_id,market_count));
        }

        return eventList;
    }

    std::vector<CompetitionResult> BetfairManager::listCompetitions(const MarketFilter& filter) {
        Response response = BetfairAPI::listCompetitions(application_token_,session_token_,filter);
        nlohmann::json data = response.get_data();

        std::vector<CompetitionResult> compList;
        compList.reserve(data.size());

        for (const auto& item : data) {
            auto competition = item["competition"];
            int comp_id = std::stoi(competition["id"].get<std::string>());
            std::string comp_name = competition["name"];
            std::string competition_region = item["competitionRegion"];
            int market_count = item["marketCount"];
            
            compList.push_back(CompetitionResult(comp_id,comp_name,market_count,competition_region));
        }
        
        return compList;
    }

    std::vector<TimeRangeResult> BetfairManager::listTimeRanges(const MarketFilter& filter,const TimeGranularity& granularity) {
        Response r = BetfairAPI::listTimeRanges(application_token_,session_token_,filter,granularity);
        nlohmann::json data = r.get_data();

        std::vector<TimeRangeResult> list;
        list.reserve(data.size());

        for (const auto& item : data) {
            int market_count = item["marketCount"];
            auto time_range = item["timeRange"];
            std::string from_time = time_range["from"];
            std::string to_time = time_range["to"];
            
            list.push_back(TimeRangeResult(market_count,from_time,to_time));
        }
        
        return list;
    }
    
    std::vector<EventResult> BetfairManager::listEvents(const MarketFilter& filter) {
        Response r = BetfairAPI::listEvents(application_token_,session_token_,filter);
        nlohmann::json data = r.get_data();

        std::vector<EventResult> events;
        events.reserve(data.size());
        
        for (auto& e : data) {
            
            int market_count = e["marketCount"];
            auto event = e["event"];
            int id = std::stoi(event["id"].get<std::string>());
            std::string name = event["name"].get<std::string>();
            std::string country_code = event.contains("countryCode") ? event["countryCode"] : "GB";
            std::string timezone = event.contains("timezone") ? event["timezone"] : "GMT";
            std::string venue = event.contains("venue") ? event["venue"] : "";
            Date open_date = Date(event["openDate"].get<std::string>());
            
            events.push_back(EventResult(market_count,id,country_code,timezone,
                venue,open_date));
        }

        return events;
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