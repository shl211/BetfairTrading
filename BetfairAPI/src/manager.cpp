#include <iostream>
#include <algorithm>
#include "BetfairAPI/manager.h"
#include "BetfairAPI/session_api.h"
#include "BetfairAPI/betting_api.h"
#include "BetfairAPI/betting_type/json_serialiser.hpp"

namespace BetfairAPI {

    namespace {
        constexpr int MINUTE_OFFSET = 2;
    }

    BetfairManager::BetfairManager(const std::string& username,
        const std::string& password,
        std::string api_key,
        Jurisdiction j,
        std::unique_ptr<Logging::ILogger> logger
    ) : jurisdiction_(j),
        api_token_(std::move(api_key)),
        refresh_time_(getTimeoutMinutes(j) - MINUTE_OFFSET),
        logger_(std::move(logger)),
        username_(username)
    {
        BetfairAPI::Response r = interactiveLogin(api_token_,username,password,j);
        auto json = r.getBody();
        bool status_code_good = r.getStatusCode() == 200;
        bool well_formed_json = json != nullptr;
        bool has_status_and_token = well_formed_json && json->contains("status") && json->contains("token");
        bool successful_login = has_status_and_token && json->at("status").get<std::string>() == "SUCCESS";

        if(status_code_good && successful_login) {
            session_token_ = json->at("token").get<std::string>();
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                logger_->info(username + " logged in successfully.");
            }
        }
        else {
            std::string error = (well_formed_json && json->contains("error")) ?
                                json->at("error").get<std::string>() : "MALFORMED JSON";
            std::string msg = username + " failed to log in. Status code: " + std::to_string(r.getStatusCode()) +
                                    " Error: " + error;
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Critical)) {
                logger_->critical(msg);
            }
            throw std::runtime_error(msg);
        }

        //start the keep alive thread
        keep_alive_thread_ = std::thread(&BetfairManager::keepAliveLoop, this);
    }

    BetfairManager::~BetfairManager() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_thread_ = true;
        }
        cv_.notify_one();
        if (keep_alive_thread_.joinable()) {
            keep_alive_thread_.join();
        }
        
        try {
            endSession();
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                logger_->info(username_ + " successfully logged out from session.");
            }
        } catch (const std::exception&) {
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                logger_->info(username_ + " failed to log out. Session still live. Manager now exiting.");
            }
            // swallow any exceptions
        }
    }

    bool BetfairManager::refreshSession() {
        Response r = keepAlive(api_token_,session_token_,jurisdiction_);
        
        auto json = r.getBody();
        bool well_formed_json = json != nullptr;
        bool status_code_good = r.getStatusCode() == 200;
        bool has_status_and_token = well_formed_json && json->contains("status") && json->contains("token");
        bool successful_refresh = has_status_and_token && json->at("status").get<std::string>() == "SUCCESS";

        return status_code_good && successful_refresh;
    }

    bool BetfairManager::endSession() {
        Response r = logout(api_token_,session_token_,jurisdiction_);

        auto json = r.getBody();
        bool well_formed_json = json != nullptr;
        bool status_code_good = r.getStatusCode() == 200;
        bool has_status = well_formed_json && json->contains("status");
        bool successful_log_out = has_status && json->at("status").get<std::string>() == "SUCCESS";

        return status_code_good && successful_log_out;
    }

    void BetfairManager::keepAliveLoop() {
        std::unique_lock<std::mutex> lock(mutex_);

        while (!stop_thread_) {
            if (cv_.wait_for(lock, std::chrono::minutes(refresh_time_)) == std::cv_status::timeout) {
                lock.unlock();
                bool success = refreshSession();
                if (!success) {
                    if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Warn)) {
                        logger_->warn("Warning: Failed to refresh Betfair session");
                    }
                } else {
                    if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                        logger_->info("Session refreshed");
                    }
                }
                lock.lock();
            }
            // If notified (e.g., destructor), loop will check stop_thread_
        }
    }

    std::vector<BettingType::EventTypeResult> BetfairManager::getEventTypes(const BettingType::MarketFilter& mf) {
        auto r = listEventTypes(api_token_,session_token_,mf,"en",jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried event types. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::EventTypeResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& event_type_result) -> BettingType::EventTypeResult {
                return BettingType::fromJson<BettingType::EventTypeResult>(event_type_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }

    std::vector<BettingType::TimeRangeResult> BetfairManager::getTimeRanges(const BettingType::MarketFilter& mf,
        BettingEnum::TimeGranularity granularity
    ) {
        auto r = listTimeRanges(api_token_,session_token_,mf,granularity,jurisdiction_);
        
        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried time ranges. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::TimeRangeResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& time_range_result) -> BettingType::TimeRangeResult {
                return BettingType::fromJson<BettingType::TimeRangeResult>(time_range_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;

    }
}

