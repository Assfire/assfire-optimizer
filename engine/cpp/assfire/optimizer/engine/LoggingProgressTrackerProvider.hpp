#pragma once

#include "ProgressTrackerProvider.hpp"

namespace assfire::optimizer {
    class LoggingProgressTrackerProvider : public ProgressTrackerProvider {
      public:
        virtual std::shared_ptr<ProgressTracker> get_progress_tracker(Session::Id session_id) const override;
    };
} // namespace assfire::optimizer