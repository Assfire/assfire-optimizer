#pragma once

#include "StateManager.hpp"
#include "assfire/optimizer/api/Session.hpp"

#include <memory>

namespace assfire::optimizer {
    class StateManagerProvider {
      public:
        virtual ~StateManagerProvider() = default;

        virtual std::shared_ptr<StateManager> get_state_manager(Session::Id session_id) const = 0;
    };
} // namespace assfire::optimizer