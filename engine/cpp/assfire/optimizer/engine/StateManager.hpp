#pragma once

#include <functional>
#include <cstdint>

namespace assfire::optimizer {
    class StateManager {
      public:
        using StateProvider = std::function<void(void*)>;
        using StateConsumer = std::function<void(uint32_t, void*)>;

        virtual ~StateManager() = default;

        void save(uint32_t size, StateProvider provide_state) {
            // [TODO]
            void* buffer = malloc(size);
            provide_state(buffer);
            free(buffer);
        }

        void load(StateConsumer consume_state) const {
            // [TODO]
            consume_state(0, nullptr);
        }
    };
} // namespace assfire::optimizer