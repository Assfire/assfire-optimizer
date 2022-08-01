#pragma once

#include "assfire/optimizer/worker/TaskProvider.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockTaskProvider : public TaskProvider {
      public:
        MOCK_METHOD(WorkerTask, load, (const std::string& task_id), (override));
    };
} // namespace assfire::optimizer