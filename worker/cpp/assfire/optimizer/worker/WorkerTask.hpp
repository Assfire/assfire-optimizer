#pragma once

#include "assfire/optimizer/api/OptimizationStrategyId.hpp"
#include "assfire/optimizer/api/Task.hpp"

namespace assfire::optimizer {
    class WorkerTask {
      public:
        const Task& task() const {
            return _task;
        }

        const OptimizationStrategyId& strategy_id() const {
            return _strategy_id;
        }

      private:
        Task _task;
        OptimizationStrategyId _strategy_id;
    };
} // namespace assfire::optimizer