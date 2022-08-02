#pragma once

#include "assfire/optimizer/api/Session.hpp"

#include <gmock/gmock.h>

namespace assfire::optimizer {
    class MockSession : public Session {
      public:
        MOCK_METHOD(Id, id, (), (const, override));
        MOCK_METHOD(void, start, (), (override));
        MOCK_METHOD(void, cancel, (), (override));
        MOCK_METHOD(void, wait_until_completed, (), (const, override));
        MOCK_METHOD(bool, wait_until_completed_for, (std::chrono::milliseconds interval_ms), (const, override));
        MOCK_METHOD(Status, current_status, (), (const, override));
        MOCK_METHOD(void, set_status_listener, (StatusListener listener), (override));
        MOCK_METHOD(std::optional<Solution>, latest_solution, (), (const, override));
        MOCK_METHOD(ProgressValue, current_progress, (), (const, override));
        MOCK_METHOD(void, set_progress_listener, (ProgressListener listener), (override));
    };
} // namespace assfire::optimizer