#pragma once

#include "assfire/optimizer/engine/OptimizationStrategy.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockOptimizationStrategy : public OptimizationStrategy {
      public:
        MOCK_METHOD(void, solve, (const Task& task, std::shared_ptr<OptimizationContext> context), (const, override));
    };
} // namespace assfire::optimizer