#pragma once

#include "Session.hpp"
#include "Task.hpp"

#include <memory>

namespace assfire::optimizer {
    class RouteOptimizer {
      public:
        virtual ~RouteOptimizer()                                            = default;
        virtual std::shared_ptr<Session> solve(const Task& task, const OptimizationStrategyId& optimization_strategy_id,
                                               bool auto_start = true) const = 0;
    };
} // namespace assfire::optimizer