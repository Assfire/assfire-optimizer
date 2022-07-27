#pragma once

#include <cstdint>
#include <functional>

namespace assfire::optimizer {
    class ProgressTracker {
      public:
        using ProgressListener = std::function<void(uint8_t)>;

        virtual ~ProgressTracker() = default;

        virtual void set_progress(uint8_t percent)                    = 0;
        virtual uint8_t progress() const                              = 0;
        virtual void set_progress_listener(ProgressListener listener) = 0;
    };
} // namespace assfire::optimizer