#include <iostream>
#include <cstdlib>

#include "BetfairAPI/LoginAPI.h"
#include "BetfairAPI/AccountAPI.h"

int main() {

    std::cout << "Testing Login API!" << std::endl;

    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");

    Response r = BetfairAPI::login(api_key,username,password);
    std::string session_token = r.get_data()["token"];
    
    Response r2 = BetfairAPI::getAccountFunds(api_key,session_token,BetfairAPI::Wallet::UK);
    std::cout << r2.get_data() << "\n";

}