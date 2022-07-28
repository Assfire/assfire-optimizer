#pragma once

#include "assfire/optimizer/engine/StateManager.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockStateManager : public StateManager {
      public:
        MOCK_METHOD(void, save, (uint32_t size, StateProvider provide_state), (override));
        MOCK_METHOD(bool, load, (StateConsumer consume_state), (const, override));
    };
} // namespace assfire::optimizer