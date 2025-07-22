#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cxxopts.hpp>

#include "BetfairAPI/manager.h"
#include "Logging/console_logger.h"
#include "Logging/coloured_console_logger.h"

template <typename T>
void printVector(const std::vector<T>& v) {
    for (const auto& i : v) {
        std::cout << i << "\n";
    }
    std::cout << "Total: " << v.size() << "\n";
}

int main(int argc, char** argv) {
    cxxopts::Options options("BetfairExample", "CLI interface to update Betfair orders.");

    options.add_options()
        ("USERNAME", "Betfair username", cxxopts::value<std::string>())
        ("PASSWORD", "Betfair password", cxxopts::value<std::string>())
        ("TOKEN", "Betfair API token", cxxopts::value<std::string>())
        ("BETID", "Selected market", cxxopts::value<std::string>())
        ("MARKETID", "Selected market", cxxopts::value<std::string>())
        ("NEWPERSISTENCE", "New persistence type: LAPSE, PERSIST, or MARKET_ON_CLOSE", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") ||
        !result.count("USERNAME") || 
        !result.count("PASSWORD") || 
        !result.count("TOKEN") || 
        !result.count("BETID") || 
        !result.count("MARKETID") || 
        !result.count("NEWPERSISTENCE")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    std::string username = result["USERNAME"].as<std::string>();
    std::string password = result["PASSWORD"].as<std::string>();
    std::string token = result["TOKEN"].as<std::string>();
    std::string market_id = result["MARKETID"].as<std::string>();
    std::string bet_id = result["BETID"].as<std::string>();
    std::string new_persistence_str = result["NEWPERSISTENCE"].as<std::string>();

    auto logger = std::make_unique<Logging::ColouredConsoleLogger>();
    logger->setLevel(Logging::LogLevel::Info);

    BetfairAPI::BetfairManager manager(
        username,
        password,
        token,
        BetfairAPI::Jurisdiction::UK,
        "en",
        std::move(logger)
    );
    // Map string to BetfairAPI::PersistenceType
    BetfairAPI::BettingEnum::PersistenceType new_persistence;
    if (new_persistence_str == "LAPSE") {
        new_persistence = BetfairAPI::BettingEnum::PersistenceType::LAPSE;
    } else if (new_persistence_str == "PERSIST") {
        new_persistence = BetfairAPI::BettingEnum::PersistenceType::PERSIST;
    } else if (new_persistence_str == "MARKET_ON_CLOSE") {
        new_persistence = BetfairAPI::BettingEnum::PersistenceType::MARKET_ON_CLOSE;
    } else {
        std::cerr << "Invalid NEWPERSISTENCE value. Use LAPSE, PERSIST, or MARKET_ON_CLOSE." << std::endl;
        return 1;
    }

    // Update order
    BetfairAPI::BettingType::UpdateInstruction update_instr;
    update_instr.betId = bet_id;
    update_instr.newPersistenceType = new_persistence;

    std::vector<BetfairAPI::BettingType::UpdateInstruction> instructions = { update_instr };

    auto response = manager.updateOrders(market_id, instructions);

    std::cout << response << "\n";

    auto check = manager.getCurrentOrders({bet_id});

    std::cout << "Check currnet orders\n"; 
    printVector(check);
    return 0;
}
