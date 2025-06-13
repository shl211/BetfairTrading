#pragma once

#include <string>
#include "betting_enum/persistence_type.hpp"

namespace BetfairAPI::BettingType {
    class UpdateInstruction {
        public:
            UpdateInstruction(std::string_view bet_id, BetfairAPI::BettingEnum::PersistenceType new_persistence_type);
            ~UpdateInstruction() = default;
            UpdateInstruction(const UpdateInstruction&) = default;
            UpdateInstruction(UpdateInstruction&&) noexcept = default;
            UpdateInstruction& operator=(const UpdateInstruction&) = default;
            UpdateInstruction& operator=(UpdateInstruction&&) noexcept = default;

            std::string getBetId() const;
            BetfairAPI::BettingEnum::PersistenceType getNewPersistenceType() const;

        private:
            std::string bet_id_;
            BetfairAPI::BettingEnum::PersistenceType new_persistence_type_;//what to update bet to
    };
}