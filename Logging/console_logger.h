#pragma once
#include "ILogger.h"
#include <iostream>
#include <mutex>

class ConsoleLogger : public ILogger {
public:
    void info(const std::string& message) override;
    void warn(const std::string& message) override;
    void error(const std::string& message) override;

private:
    std::mutex mutex_;
};