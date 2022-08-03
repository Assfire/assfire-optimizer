#pragma once

#include "assfire/optimizer/api/OptimizationStrategyId.hpp"
#include "assfire/optimizer/api/Task.hpp"

namespace assfire::optimizer {
    class WorkerTask {
      public:
        WorkerTask() = default;
        WorkerTask(Task task, OptimizationStrategyId strategy_id) : _task(task), _strategy_id(strategy_id) {}
        WorkerTask(const WorkerTask& rhs) = default;
        WorkerTask(WorkerTask&& rhs)      = default;

        WorkerTask& operator=(const WorkerTask& rhs) = default;
        WorkerTask& operator=(WorkerTask&& rhs) = default;

        bool operator==(const WorkerTask& rhs) const = default;

        void set_task(Task task) {
            _task = std::move(task);
        }

        const Task& task() const {
            return _task;
        }

        void set_strategy_id(OptimizationStrategyId strategy_id) {
            _strategy_id = std::move(strategy_id);
        }

        const OptimizationStrategyId& strategy_id() const {
            return _strategy_id;
        }

      private:
        Task _task;
        OptimizationStrategyId _strategy_id;
    };
} // namespace assfire::optimizer