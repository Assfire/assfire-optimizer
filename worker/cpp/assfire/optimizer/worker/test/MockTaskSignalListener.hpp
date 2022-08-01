#pragma once

#include "assfire/optimizer/worker/TaskSignalListener.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockTaskSignalListener : public TaskSignalListener {
      public:
        MOCK_METHOD(TaskSignal, next, (), (override));
        MOCK_METHOD(void, stop, (), (override));
    };
} // namespace assfire::optimizer