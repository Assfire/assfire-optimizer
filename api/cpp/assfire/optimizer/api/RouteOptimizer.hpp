#pragma once

#include "Session.hpp"
#include "Task.hpp"

#include <memory>

namespace assfire::optimizer {
    class RouteOptimizer {
      public:
        virtual ~RouteOptimizer()                                                                                              = default;
        virtual std::unique_ptr<Session> solve(const Task& task, const OptimizationStrategyId& optimization_strategy_id) const = 0;
    };
} // namespace assfire::optimizer