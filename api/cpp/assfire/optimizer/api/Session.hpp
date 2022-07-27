#pragma once

#include "Solution.hpp"

#include <chrono>
#include <functional>
#include <optional>

namespace assfire::optimizer {
    class Session {
      public:
        enum class Status { QUEUED, IN_PROGRESS, FINISHED, FAILED, CANCELLED };

        using StatusListener   = std::function<void(Status)>;
        using ProgressListener = std::function<void(uint8_t)>;

        virtual ~Session()                                                                 = default;
        virtual void cancel()                                                              = 0;
        virtual void wait_until_completed() const                                          = 0;
        virtual bool wait_until_completed_for(std::chrono::milliseconds interval_ms) const = 0;
        virtual Status current_status() const                                              = 0;
        virtual void set_status_listener(StatusListener listener)                          = 0;
        virtual std::optional<Solution> latest_solution() const                            = 0;
        virtual uint8_t current_progress() const                                           = 0;
        virtual void set_progress_listener(ProgressListener listener)                      = 0;
    };
} // namespace assfire::optimizer