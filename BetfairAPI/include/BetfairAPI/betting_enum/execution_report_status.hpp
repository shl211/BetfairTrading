#pragma once

namespace BetfairAPI::BettingEnum {
    enum class ExecutionReportStatus {
        SUCCESS,
        FAILURE,
        PROCESSED_WITH_ERRORS,
        TIMEOUT
    };
}