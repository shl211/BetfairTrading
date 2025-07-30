#pragma once

namespace BetfairAPI::StreamingEnum {
    enum class ChangeType {
        SUB_IMAGE,
        RESUB_DELTA,
        HEARTBEAT,
        NULLTYPE,
    };

    enum class SegmentType {
        SEG_START,
        SEG,
        SEG_END
    };
}