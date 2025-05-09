#ifndef BETFAIR_MANAGER_H
#define BETFAIR_MANAGER_H

#include <string>

class BetfairManager {

public:
    BetfairManager(std::string username, std::string password, std::string api_key);
    ~BetfairManager();

    double getAccountBalance();

private:
    std::string session_token;
    std::string application_token;

    double balance;
};

#endif