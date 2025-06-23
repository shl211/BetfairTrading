#ifndef BETFAIR_MANAGER_H
#define BETFAIR_MANAGER_H

#include <nlohmann/json.hpp>


namespace BetfairAPI {
    class BetfairManager {
    
    public:
        BetfairManager(std::string username, std::string password, std::string api_key);
        BetfairManager(const BetfairManager&) = delete;
        BetfairManager(BetfairManager&& other) noexcept;
        BetfairManager& operator=(const BetfairManager&) = delete;
        BetfairManager& operator=(BetfairManager&&) noexcept;
        ~BetfairManager();
    
        double getAccountBalance() const;


    private:
        std::string session_token_;
        std::string application_token_;
    
        double balance_;
        double discount_rate_;
        double exposure_;
        double exposure_limit_;
    
        void assignAccountInformation(const nlohmann::json& account_balance_response);
    };
}

#endif