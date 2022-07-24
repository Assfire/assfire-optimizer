#pragma once

#include <optional>
#include <functional>
#include <Solution.hpp>

namespace assfire::optimizer {
    class RouteOptimizationSession  {
    public:
        enum class Status = {
            QUEUED,
            IN_PROGRESS,
            FINISHED,
            FAILED,
            CANCELLED
        };

        using StatusListener = std::function<void(Status)>;

        virtual ~RouteOptimizationSession() = default;
        virtual void cancel() = 0;
        virtual void wait_until_completed() const = 0;
        virtual Status get_current_status() const = 0;
        void set_status_listener(StatusListener listener) = 0;
        std::optional<Solution> get_latest_solution() const = 0;
    };
}