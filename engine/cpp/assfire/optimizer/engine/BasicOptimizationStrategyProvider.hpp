#pragma once

#include "OptimizationStrategyProvider.hpp"

#include <string>
#include <unordered_map>

namespace assfire::optimizer {
    class BasicOptimizationStrategyProvider : public OptimizationStrategyProvider {
      public:
        static std::string DEFAULT;

        virtual std::shared_ptr<OptimizationStrategy> get_optimization_strategy(const OptimizationStrategyId& id) override;
        virtual const std::vector<OptimizationStrategyId>& get_available_strategies() override;

      private:
        std::unordered_map<std::string, std::shared_ptr<OptimizationStrategy>> strategies;
        std::vector<OptimizationStrategyId> available_strategies;
    };
} // namespace assfire::optimizer