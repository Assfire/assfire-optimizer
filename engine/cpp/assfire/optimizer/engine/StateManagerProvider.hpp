#pragma once

#include "StateManager.hpp"

#include <memory>

namespace assfire::optimizer {
    class StateManagerProvider {
      public:
        virtual ~StateManagerProvider() = default;

        virtual std::shared_ptr<StateManager> get_state_manager() = 0;
    };
} // namespace assfire::optimizer