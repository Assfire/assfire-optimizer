#include "BasicOptimizationStrategyProvider.hpp"

namespace assfire::optimizer {

    std::string BasicOptimizationStrategyProvider::DEFAULT = "Default";

    std::shared_ptr<OptimizationStrategy> BasicOptimizationStrategyProvider::get_optimization_strategy(const OptimizationStrategyId& id) const {
        if (id.value().empty())
        {
            return strategies.at(DEFAULT);
        }
        
        auto iter = strategies.find(id.value());
        
        if (iter != strategies.end())
        {
            return iter->second;
        }

        throw std::invalid_argument("Unsupported optimization strategy: " + id.value());
    }

    const std::vector<OptimizationStrategyId>& BasicOptimizationStrategyProvider::get_available_strategies() const {
        return available_strategies;
    }

} // namespace optimizer
