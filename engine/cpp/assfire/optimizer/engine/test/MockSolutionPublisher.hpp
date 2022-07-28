#pragma once
#include "assfire/optimizer/engine/SolutionPublisher.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockSolutionPublisher : public SolutionPublisher {
      public:
        MOCK_METHOD(void, publish, (Solution solution), (override));
        MOCK_METHOD(std::optional<Solution>, latest_solution, (), (const, override));
    };
} // namespace assfire::optimizer