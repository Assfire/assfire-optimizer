#pragma once

#include "OptimizationStrategyProvider.hpp"
#include "assfire/optimizer/api/RouteOptimizer.hpp"

#include <memory>

namespace assfire::optimizer {
    class RouteOptimizerEngine : public RouteOptimizer {
      public:
        virtual std::unique_ptr<Session> solve(const Task& task) const override;

      private:
        std::shared_ptr<OptimizationStrategyProvider> optimization_strategy_provider;
    };
} // namespace assfire::optimizer