#pragma once

#include "OptimizationStrategy.hpp"
#include "assfire/optimizer/api/OptimizationStrategyId.hpp"
#include "assfire/router/api/RoutesProvider.hpp"

#include <memory>
#include <vector>

namespace assfire::optimizer {
    class OptimizationStrategyProvider {
      public:
        virtual ~OptimizationStrategyProvider() = default;

        virtual std::shared_ptr<OptimizationStrategy> get_optimization_strategy(const OptimizationStrategyId& id) = 0;
        virtual const std::vector<OptimizationStrategyId>& get_available_strategies()                             = 0;
    };
} // namespace assfire::optimizer