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