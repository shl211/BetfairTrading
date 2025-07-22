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
    cxxopts::Options options("BetfairExample", "CLI interface to get current Betfair orders.");

    options.add_options()
        ("USERNAME", "Betfair username", cxxopts::value<std::string>())
        ("PASSWORD", "Betfair password", cxxopts::value<std::string>())
        ("TOKEN", "Betfair API token", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help") ||
        !result.count("USERNAME") || 
        !result.count("PASSWORD") || 
        !result.count("TOKEN")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    std::string username = result["USERNAME"].as<std::string>();
    std::string password = result["PASSWORD"].as<std::string>();
    std::string token = result["TOKEN"].as<std::string>();

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

    auto response = manager.getCurrentOrders();

    std::cout << "Current orders: \n";
    printVector(response); 
    return 0;
}
