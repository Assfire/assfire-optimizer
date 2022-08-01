#pragma once

#include "assfire/optimizer/worker/ProgressPublisher.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockProgressPublisher : public ProgressPublisher {
      public:
        MOCK_METHOD(void, publish, (const std::string& task_id, Session::ProgressValue progress), (override));
    };
} // namespace assfire::optimizer