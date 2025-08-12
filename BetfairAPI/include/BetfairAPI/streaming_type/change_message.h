#pragma once

#include <optional>
#include <string>
#include <ostream>
#include "BetfairAPI/date.h"
#include "BetfairAPI/utils.h"
#include "BetfairAPI/streaming_enum/message_enums.hpp"

namespace BetfairAPI::StreamingType {
    struct ChangeMessage {
        std::optional<StreamingEnum::ChangeType> changeType; //ct
        std::optional<StreamingEnum::SegmentType> segmentType;
        std::optional<int> conflateMs;
        std::optional<int> status;
        std::optional<int> heartbeatMs;
        std::optional<BetfairAPI::Date> publishTime; //pt
        std::optional<std::string> initialClk;
        std::optional<std::string> clk;
    };
    inline bool operator==(const ChangeMessage& lhs, const ChangeMessage& rhs) {
        return lhs.changeType == rhs.changeType &&
                lhs.segmentType == rhs.segmentType &&
                lhs.conflateMs == rhs.conflateMs &&
                lhs.status == rhs.status &&
                lhs.heartbeatMs == rhs.heartbeatMs &&
                lhs.publishTime == rhs.publishTime &&
                lhs.initialClk == rhs.initialClk &&
                lhs.clk == rhs.clk;
    }

    inline bool operator!=(const ChangeMessage& lhs, const ChangeMessage& rhs) {
        return !(lhs == rhs);
    }
    inline std::ostream& operator<<(std::ostream& os, const ChangeMessage& msg) {
        os << "ChangeMessage{";
        os << "changeType=" << (msg.changeType ? to_string(*msg.changeType) : "null") << ", ";
        os << "segmentType=" << (msg.segmentType ? to_string(*msg.segmentType) : "null") << ", ";
        os << "conflateMs=" << (msg.conflateMs ? std::to_string(*msg.conflateMs) : "null") << ", ";
        os << "status=" << (msg.status ? std::to_string(*msg.status) : "null") << ", ";
        os << "heartbeatMs=" << (msg.heartbeatMs ? std::to_string(*msg.heartbeatMs) : "null") << ", ";
        os << "publishTime=" << (msg.publishTime ? msg.publishTime->getIsoString() : "null") << ", ";
        os << "initialClk=" << (msg.initialClk ? *msg.initialClk : "null") << ", ";
        os << "clk=" << (msg.clk ? *msg.clk : "null");
        os << "}";
        return os;
    }
}