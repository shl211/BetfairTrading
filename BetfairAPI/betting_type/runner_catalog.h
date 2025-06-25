#pragma once

#include <string>
#include <map>


namespace BetfairAPI::BettingType {
    class RunnerCatalog {
        public:
            RunnerCatalog(long selection_id,std::string_view runner_name,
                        double handicap, int sort_priority, 
                        std::map<std::string,std::string> metadata = {});
            RunnerCatalog() = default;
            ~RunnerCatalog() = default;
            RunnerCatalog(const RunnerCatalog& other) = default;
            RunnerCatalog(RunnerCatalog&& other) noexcept = default;
            RunnerCatalog& operator=(const RunnerCatalog& other) = default;
            RunnerCatalog& operator=(RunnerCatalog&& other) noexcept = default;

            long getSelectionId() const;
            const std::string& getRunnerName() const;
            double getHandicap() const;
            int getSortPriority() const;
            const std::map<std::string, std::string>& getMetadata() const;

            private:
            long selection_id_;
            std::string runner_name_;
            double handicap_;
            int sort_priority_;
            std::map<std::string,std::string> metadata_;
    };
}