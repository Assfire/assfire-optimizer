#pragma once

#include "Solution.hpp"

#include <chrono>
#include <functional>
#include <optional>

namespace assfire::optimizer {
    class Session {
      public:
        enum class Status { QUEUED, IN_PROGRESS, FINISHED, FAILED, CANCELLED };

        using StatusListener = std::function<void(Status)>;

        virtual ~Session()                                                             = default;
        virtual void cancel()                                                          = 0;
        virtual void wait_until_completed() const                                      = 0;
        virtual bool wait_until_completed(std::chrono::milliseconds interval_ms) const = 0;
        virtual Status get_current_status() const                                      = 0;
        virtual void set_status_listener(StatusListener listener)                      = 0;
        virtual std::optional<Solution> get_latest_solution() const                    = 0;
    };
} // namespace assfire::optimizer