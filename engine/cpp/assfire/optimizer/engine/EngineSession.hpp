#pragma once

#include "OptimizationContext.hpp"
#include "OptimizationStrategy.hpp"
#include "assfire/optimizer/api/Session.hpp"
#include "assfire/optimizer/api/Task.hpp"

#include <future>
#include <memory>
#include <atomic>

namespace assfire::optimizer {
    class EngineSession : public Session {
      public:
        EngineSession(std::shared_ptr<Task> _task, std::shared_ptr<OptimizationContext> optimization_context, std::shared_ptr<OptimizationStrategy> optimization_strategy);

        virtual void cancel() override;
        virtual void wait_until_completed() const override;
        virtual bool wait_until_completed(std::chrono::milliseconds interval_ms) const override;
        virtual Status get_current_status() const override;
        virtual void set_status_listener(StatusListener listener) override;
        virtual std::optional<Solution> get_latest_solution() const override;

        void start();

      private:
        void notify_status_change();

        std::shared_ptr<Task> _task;
        std::shared_ptr<OptimizationContext> _optimization_context;
        std::shared_ptr<OptimizationStrategy> _optimization_strategy;
        std::future<void> _done_future;
        std::atomic<Status> _status;
        StatusListener _status_listener; // [TODO] consider thread safety
    };
} // namespace assfire::optimizer