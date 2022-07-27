#pragma once

#include "StateManagerProvider.hpp"

namespace assfire::optimizer {
    class DiscardingStateManagerProvider : public StateManagerProvider {
      public:
        virtual std::shared_ptr<StateManager> get_state_manager(Session::Id session_id) const override;
    };
} // namespace assfire::optimizer