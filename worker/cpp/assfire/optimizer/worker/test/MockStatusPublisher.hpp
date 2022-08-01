#pragma once

#include "assfire/optimizer/worker/StatusPublisher.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockStatusPublisher : public StatusPublisher {
      public:
        MOCK_METHOD(void, publish, (const std::string& task_id, Session::Status status), (override));
    };
} // namespace assfire::optimizer