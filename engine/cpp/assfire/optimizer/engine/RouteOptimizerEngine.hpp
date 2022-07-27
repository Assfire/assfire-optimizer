#pragma once

#include "OptimizationStrategyProvider.hpp"
#include "ProgressTrackerProvider.hpp"
#include "SolutionPublisherProvider.hpp"
#include "StateManagerProvider.hpp"
#include "assfire/optimizer/api/RouteOptimizer.hpp"

#include <memory>

namespace assfire::optimizer {
    class RouteOptimizerEngine : public RouteOptimizer {
      public:
        RouteOptimizerEngine(std::shared_ptr<OptimizationStrategyProvider> optimization_strategy_provider,
                             std::shared_ptr<SolutionPublisherProvider> solution_publisher_provider,
                             std::shared_ptr<StateManagerProvider> state_manager_provider,
                             std::shared_ptr<ProgressTrackerProvider> progress_tracker_provider);

        virtual std::unique_ptr<Session> solve(const Task& task, const OptimizationStrategyId& optimization_strategy_id) const override;

      private:
        std::shared_ptr<OptimizationStrategyProvider> _optimization_strategy_provider;
        std::shared_ptr<SolutionPublisherProvider> _solution_publisher_provider;
        std::shared_ptr<StateManagerProvider> _state_manager_provider;
        std::shared_ptr<ProgressTrackerProvider> _progress_tracker_provider;
    };
} // namespace assfire::optimizer