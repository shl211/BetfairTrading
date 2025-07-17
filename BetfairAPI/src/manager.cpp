#include <iostream>
#include <algorithm>
#include "BetfairAPI/manager.h"
#include "BetfairAPI/session_api.h"
#include "BetfairAPI/betting_api.h"
#include "BetfairAPI/betting_type/json_serialiser.hpp"

namespace BetfairAPI {

    namespace {
        constexpr int MINUTE_OFFSET = 2;
        constexpr int MAX_API_DATA = 1000;
    }

    BetfairManager::BetfairManager(const std::string& username,
        const std::string& password,
        std::string api_key,
        Jurisdiction j,
        std::string locale,
        std::unique_ptr<Logging::ILogger> logger
    ) : jurisdiction_(j),
        api_token_(std::move(api_key)),
        refresh_time_(getTimeoutMinutes(j) - MINUTE_OFFSET),
        logger_(std::move(logger)),
        username_(username),
        locale_(std::move(locale))
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
        auto r = listEventTypes(api_token_,session_token_,mf,locale_,jurisdiction_);

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
    
    std::vector<BettingType::CompetitionResult> BetfairManager::getCompetitions(const BettingType::MarketFilter& mf) {
        auto r = listCompetitions(api_token_,session_token_,mf,locale_,jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried competitions. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::CompetitionResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& competition_result) -> BettingType::CompetitionResult {
                return BettingType::fromJson<BettingType::CompetitionResult>(competition_result);
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

    std::vector<BettingType::EventResult> BetfairManager::getEvents(const BettingType::MarketFilter& mf) {
        auto r = listEvents(api_token_,session_token_,mf,locale_,jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried events. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::EventResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& event_result) -> BettingType::EventResult {
                return BettingType::fromJson<BettingType::EventResult>(event_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }

    std::vector<BettingType::MarketTypeResult> BetfairManager::getMarketTypeResults(const BettingType::MarketFilter& mf) {

        auto r = listMarketTypes(api_token_,session_token_,mf,locale_,jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried market types. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::MarketTypeResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& event_result) -> BettingType::MarketTypeResult {
                return BettingType::fromJson<BettingType::MarketTypeResult>(event_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }

    std::vector<BettingType::CountryCodeResult> BetfairManager::getCountries(const BettingType::MarketFilter& mf) {
        auto r = listCountries(api_token_,session_token_,mf,locale_,jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried market types. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::CountryCodeResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& event_result) -> BettingType::CountryCodeResult {
                return BettingType::fromJson<BettingType::CountryCodeResult>(event_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }

    std::vector<BettingType::VenueResult> BetfairManager::getVenues(const BettingType::MarketFilter& mf) {
        auto r = listVenues(api_token_,session_token_,mf,locale_,jurisdiction_);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried market types. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::VenueResult> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& event_result) -> BettingType::VenueResult {
                return BettingType::fromJson<BettingType::VenueResult>(event_result);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }

    std::vector<BettingType::MarketCatalogue> BetfairManager::getMarketCatalogues(const BettingType::MarketFilter& mf,
        const std::set<BettingEnum::MarketProjection>& market_projection,
        const std::set<BettingEnum::MarketSort>& market_sort,
        int max_results
    ) {

        if(max_results <= 0) {
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                logger_->info(username_ + " queried market catalogue. Max results <= 0 so empty return");
            }

            return {};
        }
        if(max_results > MAX_API_DATA) {
            if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
                logger_->info(username_ + " queried market catalogue. Max results >= " + 
                    std::to_string(MAX_API_DATA) + " so limited to that number");
            }
            max_results = MAX_API_DATA;
        }

        auto r = listMarketCatalogue(api_token_,session_token_,mf,market_projection,market_sort,max_results);

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info)) {
            logger_->info(username_ + " queried market catalogue. Response status code " + std::to_string(r.getStatusCode()));
        }

        std::vector<BettingType::MarketCatalogue> result;
        if(r.getBody() != nullptr) {
            const auto& body = *r.getBody();
            result.reserve(body.size());
            auto json_conversion = [](const auto& m_cat) -> BettingType::MarketCatalogue {
                return BettingType::fromJson<BettingType::MarketCatalogue>(m_cat);
            };
    
            std::transform(body.begin(), body.end(), std::back_inserter(result),json_conversion);
        }

        return result;
    }


}

