#pragma once

#include "assfire/optimizer/api/Session.hpp"
#include "ProgressTracker.hpp"

#include <memory>

namespace assfire::optimizer {
    class ProgressTrackerProvider {
      public:
        virtual ~ProgressTrackerProvider() = default;

        virtual std::shared_ptr<ProgressTracker> get_progress_tracker(Session::Id session_id) const = 0;
    };
} // namespace assfire::optimizer