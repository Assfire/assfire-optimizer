#pragma once

#include <assfire/optimizer/api/Solution.hpp>
#include <string>

namespace assfire::optimizer {
    class WorkerSolutionPublisher {
      public:
        virtual ~WorkerSolutionPublisher() = default;

        virtual void publish(const std::string& task_id, Solution solution) = 0;
    };
} // namespace assfire::optimizer