#pragma once

#include "ProgressTrackerProvider.hpp"
#include "assfire/logger/api/Logger.hpp"

namespace assfire::optimizer {
    class LoggingProgressTrackerProvider : public ProgressTrackerProvider {
      public:
        virtual std::shared_ptr<ProgressTracker> get_progress_tracker(Session::Id session_id) const override;

      private:
        std::shared_ptr<assfire::logger::Logger> _logger;
    };
} // namespace assfire::optimizer