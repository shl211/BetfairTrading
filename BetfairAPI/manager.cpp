#include "manager.h"
#include "session.h"
#include <iostream>

namespace BetfairAPI {

    namespace {
        constexpr int MINUTE_OFFSET = 2;
    }

    BetfairManager::BetfairManager(const std::string& username,
        const std::string& password,
        std::string api_key,
        Jurisdiction j
    ) : jurisdiction_(j),
        api_token_(std::move(api_key)),
        refresh_time_(getTimeoutMinutes(j) - MINUTE_OFFSET)
    {
        BetfairAPI::Response r = interactiveLogin(api_token_,username,password,j);
        auto json = r.getBody();
        bool status_code_good = r.getStatusCode() == 200;
        bool well_formed_json = json != nullptr;
        bool has_status_and_token = well_formed_json && json->contains("status") && json->contains("token");
        bool successful_login = has_status_and_token && json->at("status").get<std::string>() == "SUCCESS";

        if(status_code_good && successful_login) {
            session_token_ = json->at("token").get<std::string>();
        }
        else {
            std::string error = (well_formed_json && json->contains("error")) ?
                                json->at("error").get<std::string>() : "MALFORMED JSON";
            
            throw std::runtime_error("Failed to login. Status code: " + std::to_string(r.getStatusCode()) +
                                    " Error: " + error);
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
        } catch (const std::exception&) {
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
                    std::cerr << "Warning: Failed to refresh Betfair session\n";
                } else {
                    std::cerr << "Session refreshed for: " << api_token_;
                }
                lock.lock();
            }
            // If notified (e.g., destructor), loop will check stop_thread_
        }
    }
}

