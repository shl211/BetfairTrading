#pragma once

#include <string>
#include <map>


namespace BetfairAPI::BettingType {
    class RunnerCatalog {
        public:
            RunnerCatalog(long selection_id,std::string_view runner_name,
                        double handicap, int sort_priority, 
                        std::map<std::string,std::string> metadata = {});
            ~RunnerCatalog() = default;
            RunnerCatalog(const RunnerCatalog& other) = default;
            RunnerCatalog(RunnerCatalog&& other) noexcept = default;
            RunnerCatalog& operator=(const RunnerCatalog& other) = default;
            RunnerCatalog& operator=(RunnerCatalog&& other) noexcept = default;

            long selection_id() const;
            const std::string& runner_name() const;
            double handicap() const;
            int sort_priority() const;
            const std::map<std::string, std::string>& metadata() const;

            private:
            long selection_id_;
            std::string runner_name_;
            double handicap_;
            int sort_priority_;
            std::map<std::string,std::string> metadata_;
    };
}