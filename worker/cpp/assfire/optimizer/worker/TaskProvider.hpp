#pragma once

#include "WorkerTask.hpp"

#include <string>

namespace assfire::optimizer {
    class TaskProvider {
      public:
        virtual ~TaskProvider() = default;

        virtual WorkerTask load(const std::string &task_id) = 0;
    };
} // namespace assfire::optimizer