#include "DiscardingStateManagerProvider.hpp"

#include "StateManager.hpp"

namespace assfire::optimizer {

    class DiscardingStateManager : public StateManager {
      public:
        virtual void save(uint32_t size, StateProvider provide_state) override {
            // Do nothing here
        }
        virtual bool load(StateConsumer consume_state) const override {
            // Do nothing here
            return false;
        }
    };

    std::shared_ptr<StateManager> DiscardingStateManagerProvider::get_state_manager(Session::Id session_id) const {
        return std::make_shared<DiscardingStateManager>();
    }

} // namespace assfire::optimizer
