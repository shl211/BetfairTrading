#pragma once

#include <memory>
#include <string>
#include <deque>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <asio/ssl.hpp>
#include "Logging/ILogger.h"
#include "BetfairAPI/streaming_type/market_filter.h"
#include "BetfairAPI/streaming_type/market_data_filter.h"

namespace BetfairAPI {
    class BetfairStreaming : public std::enable_shared_from_this<BetfairStreaming> {
        public:
            BetfairStreaming(const BetfairStreaming&) = delete;
            BetfairStreaming& operator=(const BetfairStreaming&) = delete;
            BetfairStreaming(BetfairStreaming&&) noexcept = delete;
            BetfairStreaming& operator=(BetfairStreaming&&) noexcept = delete;

            //factory function
            static std::shared_ptr<BetfairStreaming> create(
                asio::io_context&, 
                asio::ssl::context&, 
                std::shared_ptr<Logging::ILogger> = nullptr
            );

            void connect(const std::string& api_token,const std::string& session_key); 
            void writeMessageAsync(std::string msg);
            std::function<void(const nlohmann::json&)> on_message;
            void subscribeToMarket(
                const StreamingType::MarketFilter& filter = {},
                const StreamingType::MarketDataFilter& md_filter = {}
            );
            int queueSize() {return outgoing_messages_.size();};

        private:
            BetfairStreaming(
                asio::io_context& io_context,
                asio::ssl::context& ssl_context,
                std::shared_ptr<Logging::ILogger> logger = nullptr
            );

            asio::io_context& io_context_;
            asio::ssl::context& ssl_context_;
            asio::ip::tcp::resolver resolver_;
            std::unique_ptr<asio::ssl::stream<asio::ip::tcp::socket>> ssl_stream_;
            std::string_view host_ = "stream-api.betfair.com";
            std::string_view port_ = "443";
            std::shared_ptr<Logging::ILogger> logger_;

            std::deque<std::string> outgoing_messages_;
            asio::streambuf read_buffer_;

            enum class ConnectionState {
                Disconnected,
                Connecting,
                Connected,
                Authenticated
            };

            ConnectionState state_ = ConnectionState::Disconnected;

            //helper functions
            void doWrite();
            void startRead();
            void handleIncomingMessage(std::string msg);

    };
}