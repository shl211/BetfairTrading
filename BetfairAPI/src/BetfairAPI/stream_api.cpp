#include "BetfairAPI/stream_api.h"
#include "BetfairAPI/streaming_type/json_serialiser.hpp"
#include <iostream>
#include <iomanip>

namespace BetfairAPI {

    namespace {
        void hexDump(const std::string& s) {
            for (unsigned char c : s) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << ' ';
            }
            std::cout << std::dec << '\n';
        }
    }


    BetfairStreaming::BetfairStreaming(std::shared_ptr<Logging::ILogger> logger)
        : ssl_context_(asio::ssl::context::tlsv12_client),
        logger_(logger)
    {
        ssl_context_.set_default_verify_paths();
        ssl_context_.set_verify_mode(asio::ssl::verify_peer);
    }

    BetfairStreaming::~BetfairStreaming() {
        if (ssl_stream_) {
            try {
                disconnect();
            } catch (const std::exception& e) {
                // Log the exception, but don't let it escape
                if(logger_) {
                    logger_->warn(std::string("[Destructor] Exception during disconnect: ") + e.what());
                }
            } catch (...) {
                if(logger_) {
                    logger_->error("[Destructor] Unknown exception during disconnect.");
                }
            }
        }
    }

    void BetfairStreaming::connect(const std::string& api_token,const std::string& session_key) {
        using asio::ip::tcp;

        // Create SSL stream wrapping a TCP socket
        ssl_stream_ = std::make_unique<asio::ssl::stream<tcp::socket>>(io_context_, ssl_context_);

        try {
            // Resolve DNS
            tcp::resolver resolver(io_context_);
            auto endpoints = resolver.resolve(host_, port_);

            // Connect TCP and SSL handshake
            asio::connect(ssl_stream_->lowest_layer(), endpoints);
            ssl_stream_->handshake(asio::ssl::stream_base::client);

            if(logger_) {
                logger_->info("Connected to Betfair Streaming API over SSL!");
            }
        } catch (const std::exception& e) {
            if(logger_) {
                logger_->error("Connection failed: " + std::string(e.what()));
            }
        }

        //send initialisation message
        nlohmann::json j;
        j["op"] = "authentication";
        j["appKey"] = api_token;
        j["session"] = session_key;

        sendMessage(j.dump());
    }

    void BetfairStreaming::disconnect() {
        if (ssl_stream_ && ssl_stream_->lowest_layer().is_open()) {
            try {
                // Attempt SSL shutdown and close TCP socket
                ssl_stream_->shutdown();
                ssl_stream_->lowest_layer().close();

                if(logger_) {
                    logger_->info("Disconnected cleanly from Betfair Streaming API.");
                }
            } catch (const std::exception& e) {
                if(logger_) {
                    logger_->warn("Error during disconnect " + std::string(e.what()));
                }
            }
        }
    }

    std::string BetfairStreaming::readMessage() {
        if (!ssl_stream_ || !ssl_stream_->lowest_layer().is_open()) {
            throw std::runtime_error("Not connected");
        }

        asio::streambuf buffer;
        asio::read_until(*ssl_stream_, buffer, "\r\n");  // Betfair messages end with CRLF

        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);  // read one line (one JSON message)

        return message;
    }

    void BetfairStreaming::sendMessage(const std::string& json_str) {
        if (!ssl_stream_ || !ssl_stream_->lowest_layer().is_open()) {
            throw std::runtime_error("Not connected");
        }

        std::string message = json_str + "\r\n";  // Betfair requires \r\n

        if(logger_ && logger_->isLevelEnabled(Logging::LogLevel::Debug)) {
            logger_->debug("Sending message: " + message);
            hexDump(message);
        }

        asio::write(*ssl_stream_, asio::buffer(message));
    }
            void subscribeToMarket(const StreamingType::MarketFilter& filter,const StreamingType::MarketDataFilter& md_filter);

    void BetfairStreaming::subscribeToMarket(const StreamingType::MarketFilter& m_filter,
        const StreamingType::MarketDataFilter& md_filter
    ) {
        nlohmann::json j;
        j["op"] = "marketSubscription";
        j["id"] = 1;
        j["marketFilter"] = m_filter;
        j["marketDataFilter"] = md_filter;  

        sendMessage(j.dump());
    }



}