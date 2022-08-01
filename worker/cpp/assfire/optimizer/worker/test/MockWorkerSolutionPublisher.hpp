#pragma once

#include "assfire/optimizer/worker/WorkerSolutionPublisher.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockWorkerSolutionPublisher : public WorkerSolutionPublisher {
      public:
        MOCK_METHOD(void, publish, (const std::string& task_id, Solution solution), (override));
    };
} // namespace assfire::optimizer