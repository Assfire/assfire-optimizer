#pragma once

#include "OptimizationContext.hpp"
#include "assfire/optimizer/api/Task.hpp"

namespace assfire::optimizer {
    class OptimizationStrategy {
      public:
        virtual ~OptimizationStrategy() = default;

        virtual void solve(const Task& task, std::shared_ptr<OptimizationContext> context) const = 0;
    };
} // namespace assfire::optimizer