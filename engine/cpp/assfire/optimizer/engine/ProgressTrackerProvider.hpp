#pragma once

#include "ProgressTracker.hpp"

#include <memory>

namespace assfire::optimizer {
    class ProgressTrackerProvider {
      public:
        virtual ~ProgressTrackerProvider() = default;

        virtual std::shared_ptr<ProgressTracker> get_progress_tracker() = 0;
    };
} // namespace assfire::optimizer