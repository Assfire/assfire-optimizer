#pragma once

#include <cstdint>
#include <functional>

namespace assfire::optimizer {
    class StateManager {
      public:
        using StateProvider = std::function<void(void*)>;
        using StateConsumer = std::function<void(uint32_t, void*)>;

        virtual ~StateManager() = default;

        virtual void save(uint32_t size, StateProvider provide_state) = 0;
        virtual bool load(StateConsumer consume_state) const          = 0;
    };
} // namespace assfire::optimizer