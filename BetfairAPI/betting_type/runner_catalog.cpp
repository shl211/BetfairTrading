#include "runner_catalog.h"

namespace BetfairAPI::BettingType {
    RunnerCatalog::RunnerCatalog(long selection_id,std::string_view runner_name,
        double handicap, int sort_priority, std::map<std::string,std::string> metadata)
        : selection_id_(selection_id), runner_name_(std::string(runner_name)), handicap_(handicap),
        sort_priority_(sort_priority), metadata_(std::move(metadata)) {}

    long RunnerCatalog::selection_id() const {
        return selection_id_;
    }

    const std::string& RunnerCatalog::runner_name() const {
        return runner_name_;
    }

    double RunnerCatalog::handicap() const {
        return handicap_;
    }

    int RunnerCatalog::sort_priority() const {
        return sort_priority_;
    }

    const std::map<std::string, std::string>& RunnerCatalog::metadata() const {
        return metadata_;
    }
}