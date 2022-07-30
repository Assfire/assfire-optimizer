#pragma once

#include "TaskSignal.hpp"

namespace assfire::optimizer {
    class TaskSignalListener {
      public:
        virtual ~TaskSignalListener() = default;
        virtual TaskSignal next()     = 0;

        virtual void interrupt() = 0;
    };
} // namespace assfire::optimizer