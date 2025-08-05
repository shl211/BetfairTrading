#include "BetfairAPI/stream_api.h"
#include "BetfairAPI/streaming_type/json_serialiser.hpp"
#include <functional>

namespace BetfairAPI {
    BetfairStreaming::BetfairStreaming(
        asio::io_context& io_context,
        asio::ssl::context& ssl_context,
        std::shared_ptr<Logging::ILogger> logger
    )
        : io_context_(io_context),
            ssl_context_(ssl_context),
            logger_(logger),
            resolver_(io_context),
            ssl_stream_(std::make_unique<asio::ssl::stream<asio::ip::tcp::socket>>(io_context, ssl_context)) {};

    std::shared_ptr<BetfairStreaming> BetfairStreaming::create(
        asio::io_context& io_context, 
        asio::ssl::context& ssl_context, 
        std::shared_ptr<Logging::ILogger> logger
    ) {
        return std::shared_ptr<BetfairStreaming>(
            new BetfairStreaming(io_context, ssl_context, std::move(logger))
        );
    }

    void BetfairStreaming::connect(const std::string& api_token,const std::string& session_key) {
        auto self = shared_from_this();

        resolver_.async_resolve(host_, port_,
            [this, self, api_token, session_key](std::error_code ec, asio::ip::tcp::resolver::results_type results) {
                bool error_log_open = logger_ && logger_->isLevelEnabled(Logging::LogLevel::Error);
                
                if (ec) {
                    if (error_log_open) logger_->error("Resolve failed: " + ec.message());
                    return;
                }

                asio::async_connect(ssl_stream_->lowest_layer(), results,
                    [this, self, error_log_open, api_token, session_key](std::error_code ec, const asio::ip::tcp::endpoint&) {
                        if (ec) {
                            if (error_log_open) logger_->error("Connect failed: " + ec.message());
                            return;
                        }

                        ssl_stream_->async_handshake(asio::ssl::stream_base::client,
                            [this, self, error_log_open, api_token, session_key](std::error_code ec) {
                                if (ec) {
                                    if (error_log_open) logger_->error("SSL handshake failed: " + ec.message());
                                    return;
                                }

                                if (logger_) logger_->info("Connected to Betfair Streaming API!");
                                std::string login_message = 
                                    "{\"op\": \"authentication\", \"appKey\": \"" + api_token +
                                    "\", \"session\": \"" + session_key + "\"}";
                                writeMessageAsync(std::move(login_message));
                                startRead();  // Begin reading messages TODO
                            }
                        );
                    }
                );
            }
        );
    }

    void BetfairStreaming::writeMessageAsync(std::string msg) {
        auto self = shared_from_this();

        // Add \r\n because Betfair messages end with CRLF
        msg += "\r\n";

        // Post the work to the io_context to ensure thread safety
        asio::post(io_context_, [this, self, msg = std::move(msg)]() mutable {
            bool write_in_progress = !outgoing_messages_.empty();
            outgoing_messages_.push_back(std::move(msg));

            if (logger_ && logger_->isLevelEnabled(Logging::LogLevel::Debug)) {
                logger_->debug("Message queued, queue size: " + std::to_string(outgoing_messages_.size()));
            }

            // If no write is currently in progress, start one
            if (!write_in_progress) {
                doWrite();
            }
        });
    }

    void BetfairStreaming::doWrite() {
        auto self = shared_from_this();

        asio::async_write(*ssl_stream_,
            asio::buffer(outgoing_messages_.front()),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    outgoing_messages_.pop_front();
                    if (!outgoing_messages_.empty()) {
                        doWrite();
                    }
                } else {
                    if (logger_ && logger_->isLevelEnabled(Logging::LogLevel::Error)) {
                        logger_->error("Write failed: " + ec.message());
                    }
                    // Handle error: e.g., close connection or retry
                }
            }
        );
    }

    void BetfairStreaming::startRead() {
        auto self = shared_from_this();

        // Start reading until CRLF (Betfair messages end with \r\n)
        asio::async_read_until(*ssl_stream_, read_buffer_, "\r\n",
            [this, self](std::error_code ec, std::size_t bytes_transferred) {
                if (ec) {
                    if (logger_ && logger_->isLevelEnabled(Logging::LogLevel::Error)) {
                        logger_->error("Read failed: " + ec.message());
                    }
                    state_ = ConnectionState::Disconnected;
                    return;  // Exit read loop
                }

                // Extract the message
                std::istream is(&read_buffer_);
                std::string message;
                std::getline(is, message); // removes '\n', leaves '\r' if present
                if (!message.empty() && message.back() == '\r') {
                    message.pop_back();
                }

                if (logger_ && logger_->isLevelEnabled(Logging::LogLevel::Debug)) {
                    logger_->debug("Received message: " + message);
                }

                // Process message (authentication response, updates, etc.)
                handleIncomingMessage(std::move(message));

                // Continue reading
                startRead();
            }
        );
    }

    void BetfairStreaming::handleIncomingMessage(std::string msg) {
        nlohmann::json j = nlohmann::json::parse(std::move(msg));
        if(j["op"] == "connection") {
            if(j["status"] == "SUCCESS") {
                state_ = ConnectionState::Authenticated;
            }
        }

        if (on_message) {
            on_message(j);
        }
    }

    void BetfairStreaming::subscribeToMarket(
        const StreamingType::MarketFilter& m_filter,
        const StreamingType::MarketDataFilter& md_filter
    ) {
        nlohmann::json j;
        j["op"] = "marketSubscription";
        j["id"] = 1;
        j["marketFilter"] = m_filter;
        j["marketDataFilter"] = md_filter;  

        writeMessageAsync(j.dump());
    }
}