#include <iostream>
#include <cstdlib>

#include "BetfairAPI/BetfairManager.h"

int main() {

    std::cout << "Testing Login API!" << std::endl;

    const char* api_key = std::getenv("APIKEYDELAY");
    const char* username = std::getenv("USERNAME");
    const char* password = std::getenv("PASSWORD");

    BetfairManager session = BetfairManager(username,password,api_key);

    std::cout << session.getAccountBalance() << "\n";

}