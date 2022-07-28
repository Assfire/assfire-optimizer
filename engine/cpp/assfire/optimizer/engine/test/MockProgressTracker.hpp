#pragma once

#include "assfire/optimizer/engine/ProgressTracker.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockProgressTracker : public ProgressTracker {
      public:
        MOCK_METHOD(void, set_progress, (uint8_t percent), (override));
        MOCK_METHOD(uint8_t, progress, (), (const, override));
        MOCK_METHOD(void, set_progress_listener, (ProgressListener listener), (override));
    };
} // namespace assfire::optimizer