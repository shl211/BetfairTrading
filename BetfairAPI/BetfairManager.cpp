#include "BetfairManager.h"
#include "LoginAPI.h"
#include "AccountAPI.h"

BetfairManager::~BetfairManager() {
    //do nothing
};

BetfairManager::BetfairManager(std::string username, std::string password, std::string api_key) :
    application_token(std::string(api_key)) {
    
    //get login and session information
    Response r = BetfairAPI::login(application_token,username,password);
    auto login_info = r.get_data();
    session_token = login_info["token"];

    //initialise with aaccount information
    r = BetfairAPI::getAccountFunds(application_token,session_token);
    auto account_info = r.get_data();
    balance = account_info["availableToBetBalance"];

};

double BetfairManager::getAccountBalance() {
    return balance;
}