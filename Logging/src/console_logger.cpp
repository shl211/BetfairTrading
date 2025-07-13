#include "Logging/console_logger.h"

void ConsoleLogger::info(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[INFO] " << message << "\n";
}

void ConsoleLogger::warn(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "[WARN] " << message << "\n";
}

void ConsoleLogger::error(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cerr << "[ERROR] " << message << "\n";
}