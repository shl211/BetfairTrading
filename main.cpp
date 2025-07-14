#include <iostream>
#include <thread>
#include <chrono>
#include "BetfairAPI/manager.h"
#include "BetfairAPI/session.h"
#include "Logging/console_logger.h"
#include "Logging/file_logger.h"

int main() {
    const char* USERNAME = std::getenv("USERNAME");
    const char* PASSWORD = std::getenv("PASSWORD");
    const char* APIKEYDELAY = std::getenv("APIKEYDELAY");
    if (!USERNAME || !PASSWORD || !APIKEYDELAY) {
        std::cerr << "Environment variables BETFAIR_USERNAME, BETFAIR_PASSWORD, or BETFAIR_APIKEYDELAY not set." << std::endl;
        return 1;
    }

    auto r = BetfairAPI::BetfairManager(USERNAME,
        PASSWORD,
        APIKEYDELAY,
        BetfairAPI::Jurisdiction::UK,
        std::make_unique<Logging::SpdFileLogger>("a.log"));

    //std::this_thread::sleep_for(std::chrono::minutes(5));
}