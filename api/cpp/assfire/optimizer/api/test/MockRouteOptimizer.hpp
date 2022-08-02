#pragma once

#include "assfire/optimizer/api/RouteOptimizer.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockRouteOptimizer : public RouteOptimizer {
      public:
        MOCK_METHOD(std::shared_ptr<Session>, solve, (const Task& task, const OptimizationStrategyId& optimization_strategy_id, bool auto_start),
                    (const, override));
    };
} // namespace assfire::optimizer