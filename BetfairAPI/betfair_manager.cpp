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

    nlohmann::json BetfairManager::listEventTypes(const BettingType::MarketFilter& mf,const std::string& locale) const {
        auto r = BetfairAPI::listEventTypes(application_token_,session_token_,mf,locale);
        return r.get_data();
    }

    nlohmann::json BetfairManager::listCompetitions(const BettingType::MarketFilter& mf,const std::string& locale) const {
        auto r = BetfairAPI::listCompetitions(application_token_,session_token_,mf,locale);
        return r.get_data();
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