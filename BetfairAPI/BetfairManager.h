#ifndef BETFAIR_MANAGER_H
#define BETFAIR_MANAGER_H

#include <nlohmann/json.hpp>
#include "MarketFilter.h"

namespace BetfairAPI {
    class BetfairManager {
    
    public:
        BetfairManager(std::string username, std::string password, std::string api_key);
        BetfairManager(const BetfairManager&) = delete;
        BetfairManager& operator=(const BetfairManager&) = delete;
        ~BetfairManager();
    
        double getAccountBalance();
        nlohmann::json listEventTypes(const MarketFilter& filter=MarketFilter{});
    
    private:
        std::string session_token;
        std::string application_token;
    
        double balance;
        double discount_rate;
        double exposure;
        double exposure_limit;
    
        void assignAccountInformation(const nlohmann::json& account_balance_response);
    };
}

#endif