#pragma once

#include <memory>
#include <atomic>
#include <string>
#include <asio.hpp>
#include <asio/ssl.hpp>
#include <Logging/ILogger.h>
#include "BetfairAPI/streaming_type/market_filter.h"

namespace BetfairAPI {
    class BetfairStreaming {
        public:
            BetfairStreaming(std::shared_ptr<Logging::ILogger> logger = nullptr);
            ~BetfairStreaming(); 

            void connect(const std::string& api_token,const std::string& session_key);
            void disconnect();
            std::string readMessage();
            void sendMessage(const std::string& json_str);
            void subscribeToMarket(const StreamingType::MarketFilter& filter);

        private:
            asio::io_context io_context_;
            asio::ssl::context ssl_context_;
            std::unique_ptr<asio::ssl::stream<asio::ip::tcp::socket>> ssl_stream_;
            std::string_view host_ = "stream-api.betfair.com";
            std::string_view port_ = "443";

            std::shared_ptr<Logging::ILogger> logger_;

            std::atomic<int> msg_id_ = 1;
    };


}