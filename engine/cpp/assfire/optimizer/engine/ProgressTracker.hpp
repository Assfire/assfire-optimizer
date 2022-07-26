#pragma once

#include <cstdint>

namespace assfire::optimizer {
    class ProgressTracker {
      public:
        virtual ~ProgressTracker() = default;

        virtual void set_progress(uint8_t percent) = 0;
        virtual uint8_t progress() const           = 0;
    };
} // namespace assfire::optimizer