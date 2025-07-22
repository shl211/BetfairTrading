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

        std::string printResponse(const Response& r,bool printResponseBody,bool printRequestBody) {
            std::string s {"Queried " + r.getRequestTarget() + " (Status " + std::to_string(r.getStatusCode()) +  ")"};

            if(printRequestBody) {
                s += ", Request body: ";
                if (r.getBody()) {
                    s += r.getBody()->dump();
                } else {
                    s += "N/A";
                }
            }

            if(printResponseBody) {
                s += " Response body: ";
                if (r.getRequestBody()) {
                    s += r.getRequestBody()->dump();
                } else {
                    s += "N/A";
                }
            }

            return s;
        }
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
        setLoggingFlags();
        
        BetfairAPI::Response r = interactiveLogin(api_token_,username,password,j);
        auto json = r.getBody();
        bool status_code_good = r.getStatusCode() == 200;
        bool well_formed_json = json != nullptr;
        bool has_status_and_token = well_formed_json && json->contains("status") && json->contains("token");
        bool successful_login = has_status_and_token && json->at("status").get<std::string>() == "SUCCESS";

        if(status_code_good && successful_login) {
            session_token_ = json->at("token").get<std::string>();
            if(is_info_level_) {
                logger_->info(username + " logged in successfully.");
            }

            if(is_debug_level_) {
                logger_->debug(printResponse(r,true,true));
            }
        }
        else {
            std::string error = (well_formed_json && json->contains("error")) ?
                                json->at("error").get<std::string>() : "MALFORMED JSON";
            std::string msg = username + " failed to log in. Status code: " + std::to_string(r.getStatusCode()) +
                                    " Error: " + error;
            if(is_critical_level_) {
                logger_->critical(msg);
                logger_->critical(printResponse(r, true, true));
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
            if(is_info_level_) {
                logger_->info(username_ + " successfully logged out from session.");
            }
        } catch (const std::exception&) {
            if(is_info_level_) {
                logger_->info(username_ + " failed to log out. Session still live. Manager now exiting.");
            }
            // swallow any exceptions
        }
    }

    void BetfairManager::setLoggingFlags() {
        is_debug_level_ = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Debug);
        is_info_level_ = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Info);
        is_critical_level_ = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Critical);
        is_error_level_ = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Error);
        is_warn_level_ = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Warn);
    }

    bool BetfairManager::refreshSession() {
        Response r = keepAlive(api_token_,session_token_,jurisdiction_);
        
        auto json = r.getBody();
        bool well_formed_json = json != nullptr;
        bool status_code_good = r.getStatusCode() == 200;
        bool has_status_and_token = well_formed_json && json->contains("status") && json->contains("token");
        bool successful_refresh = has_status_and_token && json->at("status").get<std::string>() == "SUCCESS";

        if (!successful_refresh && is_debug_level_) {
            logger_->debug(printResponse(r, true, true));
        }

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
                    if(is_warn_level_) {
                        logger_->warn("Warning: Failed to refresh Betfair session");
                    }
                } else {
                    if(is_info_level_) {
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

        if(is_info_level_) {
            logger_->info(username_ + " queried event types." + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried event types." + printResponse(r,true,true));
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

        if(is_info_level_) {
            logger_->info(username_ + " queried competitions. " + printResponse(r,false,false));
        }
        
        if(is_debug_level_) {
            logger_->debug(username_ + " queried competitions. " + printResponse(r,true,true));
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
        
        if(is_info_level_) {
            logger_->info(username_ + " queried time ranges. " + printResponse(r,false,false));
        }
        
        if(is_debug_level_) {
            logger_->debug(username_ + " queried time ranges. " + printResponse(r,true,true));
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

        if(is_info_level_) {
            logger_->info(username_ + " queried events. " + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried events. " + printResponse(r,true,true));
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

        if(is_info_level_) {
            logger_->info(username_ + " queried market types. " + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried market types. " + printResponse(r,true,true));
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

        if(is_info_level_) {
            logger_->info(username_ + " queried countries. " + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried countries. " + printResponse(r,true,true));
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

        if(is_info_level_) {
            logger_->info(username_ + " queried venues. " + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried venues. " + printResponse(r,true,true));
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
            if(is_info_level_) {
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

        if(is_info_level_) {
            logger_->info(username_ + " queried market catalogue. " + printResponse(r,false,false));
        }

        if(is_debug_level_) {
            logger_->debug(username_ + " queried market catalogue. " + printResponse(r,true,true));
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

    std::vector<BettingType::CurrentOrderSummary> BetfairManager::getCurrentOrders(
        const std::set<std::string> bet_ids,
        const std::set<std::string> market_ids,
        std::optional<BettingEnum::OrderProjection> order_projection,
        const std::set<std::string> customer_order_refs,
        const std::set<std::string> customer_strategy_refs,
        std::optional<BettingType::TimeRange> date_range,
        std::optional<BettingEnum::OrderBy> order_by,
        std::optional<BettingEnum::SortDir> sort_dir,
        bool include_item_description,
        bool include_source_id
    ) {
        int search_start = 0;
        constexpr int MAX_RESULTS_PER_QUERY = 1000;

        std::vector<BettingType::CurrentOrderSummary> results;

        //market_id + bet_id size <= 250 else rejection
        constexpr int MAX_CHUNK_SIZE = 250;
        if(int total_size = std::size(market_ids) + std::size(bet_ids); total_size > MAX_CHUNK_SIZE) {
            if(is_warn_level_) {
                logger_->warn("While querying current orders, std::size(market_ids) + std::size(bet_ids) exceeded 250 items. You have " + 
                    std::to_string(total_size) + ". API call skipped as listCurrentOrders/ accepts hard limit of 250 of market_ids + bet_ids.");
            }
            return results;
        }

        BettingType::CurrentOrderSummaryReport report;
        report.moreAvailable = true;//dummy variable for loop purposes
        
        while (report.moreAvailable) {
            auto response = listCurrentOrders(api_token_,session_token_,bet_ids,market_ids,
                order_projection,customer_order_refs,customer_strategy_refs,
                date_range,order_by,sort_dir,search_start,MAX_RESULTS_PER_QUERY,
                include_item_description,include_source_id,jurisdiction_
            );

            if(is_info_level_) {
                logger_->info(username_ + " queried current orders. " + printResponse(response,false,false));
            }
    
            if(is_debug_level_) {
                logger_->debug(username_ + " queried current orders. " + printResponse(response,true,true));
            }

            if(auto body = response.getBody()) {
                report = BettingType::fromJson<BettingType::CurrentOrderSummaryReport>(*body);
                results.insert(results.end(),
                    std::make_move_iterator(report.currentOrders.begin()),
                    std::make_move_iterator(report.currentOrders.end())
                );
                search_start += MAX_RESULTS_PER_QUERY;
            } 
            else {
                report.moreAvailable = false; //terminating condition if no valid response
            }
        }

        return results;
    }

    std::vector<BettingType::ClearedOrderSummary> BetfairManager::getClearedOrders(
        BettingEnum::BetStatus bet_status,
        std::optional<BettingType::TimeRange> settled_date_range,
        const std::set<std::string>& event_type_ids,
        const std::set<std::string>& event_ids,
        const std::set<std::string>& market_ids,
        const std::set<BettingType::RunnerId>& runner_ids,
        const std::set<std::string> bet_ids,
        std::optional<BettingEnum::Side> side,
        std::optional<BettingEnum::GroupBy> group_by,
        bool include_item_description,
        bool include_source_id
    ) {
        int search_start = 0;
        constexpr int MAX_RESULTS_PER_QUERY = 1000;

        std::vector<BettingType::ClearedOrderSummary> results;

        BettingType::ClearedOrderSummaryReport report;
        
        constexpr int MAX_CHUNK_SIZE = 1000;
        if(int total_size = std::size(bet_ids); total_size > MAX_CHUNK_SIZE) {
            if(is_warn_level_) {
                logger_->warn("While querying cleared orders, std::size(bet_ids) exceeded 1000 items. You have " +
                    std::to_string(total_size) + ". API call skipped as listClearedOrders accepts a hard limit of 1000 bet_ids.");
            }
            return results;
        }


        report.moreAvailable = true;//dummy variable for auto-pagination purposes

        while (report.moreAvailable) {
            auto response = listClearedOrders(api_token_,session_token_,
                bet_status,event_type_ids,event_ids,market_ids,runner_ids,
                bet_ids,side,settled_date_range,group_by,include_item_description,
                include_source_id,locale_,search_start,MAX_RESULTS_PER_QUERY,jurisdiction_
            );

            if(is_info_level_) {
                logger_->info(username_ + " queried cleared orders. " + printResponse(response,false,false));
            }

            if(is_debug_level_) {
                logger_->debug(username_ + " queried cleared orders. " + printResponse(response,true,true));
            }

            if(auto body = response.getBody()) {
                report = BettingType::fromJson<BettingType::ClearedOrderSummaryReport>(*body);
                results.insert(results.end(),
                    std::make_move_iterator(report.clearedOrders.begin()),
                    std::make_move_iterator(report.clearedOrders.end())
                );
                search_start += MAX_RESULTS_PER_QUERY;
            } 
            else {
                report.moreAvailable = false; //terminating condition if no valid response
            }
        }

        return results;
    }

    //async on will return immediatley
    //use listCurrentOrders to get async orders
    BettingType::PlaceExecutionReport BetfairManager::placeOrders(
        std::string market_id,
        const std::vector<BettingType::PlaceInstruction>& instructions,
        std::optional<BettingType::MarketVersion> market_version,
        std::optional<std::string> customer_ref,
        std::optional<std::string> customer_strategy_ref,
        std::optional<bool> async
    ) {
        const int MAX_INSTRUCTIONS = jurisdiction_ != Jurisdiction::ITALY ? 200 : 50;

        const int instruction_size = std::size(instructions);
        if(instruction_size > MAX_INSTRUCTIONS) {
            if(is_warn_level_) {
                logger_->warn("Attempted to place " + std::to_string(instruction_size) +
                    " orders, which exceeds the maximum allowed (" + std::to_string(MAX_INSTRUCTIONS) +
                    ") for jurisdiction " + std::to_string(static_cast<int>(jurisdiction_)) + ". No orders placed.");
            }
            return {};
        }

        auto response = BetfairAPI::placeOrders(
            api_token_,session_token_,market_id,instructions,
            market_version,customer_ref,customer_strategy_ref,async
        );

        if(is_info_level_) {
            logger_->info(username_ + " placed " + std::to_string(instruction_size) + " orders. " 
            + printResponse(response,false,false));
        }
        
        if(is_debug_level_) {
            logger_->debug(username_ + " placed " + std::to_string(instruction_size) + " orders. " 
            + printResponse(response,true,true));
        }

        BettingType::PlaceExecutionReport report;
        if(response.getBody() != nullptr) {
            report = BettingType::fromJson<BettingType::PlaceExecutionReport>(*response.getBody());
        }

        return report;
    }

    BettingType::CancelExecutionReport BetfairManager::cancelOrders(
        std::string market_id,
        const std::vector<BettingType::CancelInstruction>& instructions,
        std::optional<std::string> customer_ref
    ) {
        auto response = BetfairAPI::cancelOrders(
            api_token_,session_token_,market_id,instructions,
            customer_ref,jurisdiction_
        );

        std::string msg;
        if(market_id.empty() && instructions.empty()) {
            msg = "ALL ORDERS PLACED";
        } 
        else if(!market_id.empty()) {
            msg = "ALL ORDERS IN MARKET " + market_id;
        }
        else {
            msg = std::to_string(std::size(instructions));
        }

        if(is_info_level_) {
            logger_->info(username_ + " cancelled " + msg + " orders. " 
            + printResponse(response,false,false));
        }
        
        if(is_debug_level_) {
            logger_->debug(username_ + " cancelled " + msg + " orders. " 
            + printResponse(response,true,true));
        }

        BettingType::CancelExecutionReport report;
        if(response.getBody() != nullptr) {
            report = BettingType::fromJson<BettingType::CancelExecutionReport>(*response.getBody());
        }

        return report;
    }

    BettingType::UpdateExecutionReport BetfairManager::updateOrders(
        std::string market_id,
        const std::vector<BettingType::UpdateInstruction>& instructions,
        std::optional<std::string> customer_ref
    ) {
        auto response = BetfairAPI::updateOrders(api_token_,session_token_,
            market_id,instructions,customer_ref,jurisdiction_
        );

        int instruction_size = std::size(instructions);
        if(is_info_level_) {
            logger_->info(username_ + " updated " + std::to_string(instruction_size) + " orders. " 
            + printResponse(response,false,false));
        }
        
        if(is_debug_level_) {
            logger_->debug(username_ + " updated " + std::to_string(instruction_size) + " orders. " 
            + printResponse(response,true,true));
        }

        BettingType::UpdateExecutionReport report;
        if(response.getBody() != nullptr) {
            report = BettingType::fromJson<BettingType::UpdateExecutionReport>(*response.getBody());
        }

        return report;
    }
}

