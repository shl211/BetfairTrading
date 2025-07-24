#include "BetfairAPI/stream_api.h"
#include <iostream>

namespace BetfairAPI {
    BetfairStreaming::BetfairStreaming()
        : ssl_context_(asio::ssl::context::tlsv12_client)
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
                std::cerr << "[Destructor] Exception during disconnect: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "[Destructor] Unknown exception during disconnect." << std::endl;
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

            // Connect TCP
            asio::connect(ssl_stream_->lowest_layer(), endpoints);

            // Perform SSL handshake
            ssl_stream_->handshake(asio::ssl::stream_base::client);

            std::cout << "Connected to Betfair Streaming API over SSL!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
        }

        //send initialisation message
        std::string msg = R"({
            "op": "authentication",
            "appKey": ")" + api_token + R"(",
            "session": ")" + session_key + R"("
        })";

        sendMessage(msg);
    }

    void BetfairStreaming::disconnect() {
        if (ssl_stream_ && ssl_stream_->lowest_layer().is_open()) {
            try {
                // Attempt SSL shutdown
                ssl_stream_->shutdown();

                // Close the TCP socket
                ssl_stream_->lowest_layer().close();

                std::cout << "Disconnected cleanly from Betfair Streaming API." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error during disconnect: " << e.what() << std::endl;
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

        asio::write(*ssl_stream_, asio::buffer(message));
}
}