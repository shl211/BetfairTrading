#pragma once

namespace BetfairAPI::BettingEnum {
    enum class ExecutionReportErrorCode {
        ERROR_IN_MATCHER, //The matcher is not healthy. Please note: The error will also be returned is you attempt concurrent 'cancel all' bets requests using cancelOrders which isn't permitted.
        PROCESSED_WITH_ERRORS, //The order itself has been accepted, but at least one (possibly all) actions have generated errors
        BET_ACTION_ERROR, //There is an error with an action that has caused the entire order to be rejected. Check the instructionReports errorCode for the reason for the rejection of the order.
        INVALID_ACCOUNT_STATE,//Order rejected due to the account's status (suspended, inactive, dup cards)        INVALID_WALLET_STATUS,
        INVALID_WALLET_STATUS,//Order rejected due to the account's wallet's status
        INSUFFICIENT_FUNDS,//Account has exceeded its exposure limit or available to bet limit
        LOSS_LIMIT_EXCEEDED,//The account has exceed the self imposed loss limit
        MARKET_SUSPENDED,//Market is suspended
        MARKET_NOT_OPEN_FOR_BETTING,//Market is not open for betting. It is either not yet active, suspended or closed awaiting settlement.
        DUPLICATE_TRANSACTION,//Duplicate customer reference data submitted - Please note: There is a time window associated with the de-duplication of duplicate submissions which is 60 second
        INVALID_ORDER,//Order cannot be accepted by the matcher due to the combination of actions. For example, bets being edited are not on the same market, or order includes both edits and placement
        INVALID_MARKET_ID,//Market doesn't exist
        PERMISSION_DENIED,//Business rules do not allow order to be placed. You are either attempting to place the order using a Delayed Application Key or from a restricted jurisdiction (i.e. USA)
        DUPLICATE_BETIDS,//Duplicate bet ids found. For example, you've included the same betId more than once in a single cancelOrders request.
        NO_ACTION_REQUIRED,//Order hasn't been passed to matcher as system detected there will be no state change
        SERVICE_UNAVAILABLE,//The requested service is unavailable
        REJECTED_BY_REGULATOR,//The regulator rejected the order. On the Italian Exchange this error will occur if more than 50 bets are sent in a single placeOrders request.
        NO_CHASING,//A specific error code that relates to Spanish Exchange markets only which indicates that the bet placed contravenes the Spanish regulatory rules relating to loss chasing.
        REGULATOR_IS_NOT_AVAILABLE,//The underlying regulator service is not available.
        TOO_MANY_INSTRUCTIONS,//The amount of orders exceeded the maximum amount allowed to be executed
        INVALID_MARKET_VERSION,//The supplied market version is invalid. Max length allowed for market version is 12.
        INVALID_PROFIT_RATIO,//The order falls outside the permitted price and size combination.
        NO_CHANGE,//Trying to update the persistence type to the one it already has.
    };
}