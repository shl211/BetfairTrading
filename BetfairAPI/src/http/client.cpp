#include <cpr/cpr.h>
#include <thread>
#include <chrono>
#include "http/client.h"

namespace BetfairAPI::HTTP {

    namespace {
        void logRetry(const std::shared_ptr<Logging::ILogger>& logger, const std::string& url, int retries) {
            if(logger && logger->isLevelEnabled(Logging::LogLevel::Debug)) {
                logger->debug("Retrying request to " + url + " attempt " + std::to_string(retries));
            }
        }

        void logResponse(const std::shared_ptr<Logging::ILogger>& logger,
            const Request& request,
            const Response& response
        ) {
            if(logger && logger->isLevelEnabled(Logging::LogLevel::Debug)) {
                std::string json_body = response.getBody() ? response.getBody()->dump() : "<null>"; 
                
                logger->debug("Queried " + request.url() + " (status " + 
                    std::to_string(response.getStatusCode()) + "); Request: " +
                    request.body() + "; Response: " + json_body);
            }
            else if(logger && logger->isLevelEnabled(Logging::LogLevel::Info)) {
                logger->info("Request to " + request.url() + " (code " + std::to_string(response.getStatusCode()) + ")");
            }
        }

        cpr::Response makeRequest(const cpr::Url& url,
            const cpr::Header& header,
            const cpr::Body& body,
            Request::HttpMethod method
        ) {
            switch(method) {
                case Request::HttpMethod::GET:
                    return cpr::Get(url,header,body);
                case Request::HttpMethod::POST:
                    return cpr::Post(url,header,body);
                case Request::HttpMethod::PUT:
                    return cpr::Put(url,header,body);
                case Request::HttpMethod::DELETE:
                    return cpr::Delete(url,header,body);
            }

            assert(false && "Invalid HTTP method");
            std::terminate();
        }

        Response convertResponse(cpr::Response&& r) {
            // convertResponse takes ownership of cpr::Response data and
            // leaves the input in a valid but unspecified state.
            // Do not use the input cpr::Response after calling this function.
            return Response{static_cast<int>(r.status_code),std::move(r.text)};
        }

        cpr::Response retryRequest(const cpr::Url& url,
            const cpr::Header& header,
            const cpr::Body& body,
            Request::HttpMethod method,
            int max_retries,
            const std::shared_ptr<Logging::ILogger>& logger
        ) {
            int retries = 0;
            using namespace std::chrono_literals;
            constexpr auto retry_delay = 500ms;

            cpr::Response cpr_response;
            while(retries < max_retries) {
                cpr_response = BetfairAPI::HTTP::makeRequest(url,header,body,method); 

                if(cpr_response.status_code < 300 && cpr_response.status_code >= 200) {
                    //success
                    break;
                }

                ++retries;
                logRetry(logger,url.str(),retries);

                std::this_thread::sleep_for(retry_delay); // Wait before next retry
            }

            return cpr_response;
        }
    }

    HTTPClient::HTTPClient(std::shared_ptr<Logging::ILogger> logger) 
        : logger_(std::move(logger)) {}; 

    Response HTTPClient::makeRequest(const Request& request) {
        cpr::Url url{request.url()};
        cpr::Header header{request.header().begin(), request.header().end()};
        cpr::Body body{request.body()};

        auto cpr_response = retryRequest(url,header,body,request.method(),max_retries_,logger_);

        auto response = convertResponse(std::move(cpr_response));

        logResponse(logger_,request,response);

        return response;
    }
}