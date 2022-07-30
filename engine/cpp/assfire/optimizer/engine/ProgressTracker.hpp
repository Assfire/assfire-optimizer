#pragma once

#include <cstdint>
#include <functional>

namespace assfire::optimizer {
    class ProgressTracker {
      public:
        using ProgressValue    = uint8_t;
        using ProgressListener = std::function<void(ProgressValue)>;

        virtual ~ProgressTracker() = default;

        virtual void set_progress(ProgressValue percent)              = 0;
        virtual ProgressValue progress() const                        = 0;
        virtual void set_progress_listener(ProgressListener listener) = 0;
    };
} // namespace assfire::optimizer