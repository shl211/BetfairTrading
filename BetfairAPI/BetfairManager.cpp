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
        if (!application_token.empty()) {
            volatile char* p = &application_token[0];
            std::memset(const_cast<char*>(p), 0, application_token.size());
            std::atomic_thread_fence(std::memory_order_release);
            application_token.clear();
        }
        // Clear session_token
        if (!session_token.empty()) {
            volatile char* p = &session_token[0];
            std::memset(const_cast<char*>(p), 0, session_token.size());
            std::atomic_thread_fence(std::memory_order_release);
            session_token.clear();
        }
    }
    
    BetfairManager::BetfairManager(std::string username, std::string password, std::string api_key) :
        application_token(std::string(api_key)) {
        
        //get login and session information
        Response r = BetfairAPI::login(application_token,username,password);
        auto login_info = r.get_data();
        session_token = login_info["token"];
    
        //initialise with account information
        r = BetfairAPI::getAccountFunds(application_token,session_token);
        auto account_info = r.get_data();
        assignAccountInformation(account_info);
    };
    
    double BetfairManager::getAccountBalance() {
        return balance;
    }

    nlohmann::json BetfairManager::listEventTypes(const MarketFilter& filter) {
        Response response = BetfairAPI::listEventTypes(application_token,session_token,filter);
        return response.get_data();
    }

    
    
    /******************************************************************************
    * PRIVATE
    ******************************************************************************/
    
    void BetfairManager::assignAccountInformation(const nlohmann::json& account_balance_response) {
        balance = account_balance_response["availableToBetBalance"];
        discount_rate = account_balance_response["discountRate"];
        exposure = account_balance_response["exposure"];
        exposure_limit = account_balance_response["exposureLimit"];
    }
}