#pragma once

#include "assfire/optimizer/worker/HeartbeatPublisher.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockHeartbeatPublisher : public HeartbeatPublisher {
      public:
        MOCK_METHOD(void, start, (), (override));
        MOCK_METHOD(void, stop, (), (override));
    };
} // namespace assfire::optimizer