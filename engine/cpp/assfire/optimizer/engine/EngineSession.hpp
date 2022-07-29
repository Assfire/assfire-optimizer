#pragma once

#include "OptimizationContext.hpp"
#include "OptimizationStrategy.hpp"
#include "assfire/optimizer/api/Session.hpp"
#include "assfire/optimizer/api/Task.hpp"
#include "assfire/logger/api/Logger.hpp"

#include <atomic>
#include <future>
#include <memory>

namespace assfire::optimizer {
    class EngineSession : public Session {
      public:
        EngineSession(std::shared_ptr<Task> _task, std::shared_ptr<OptimizationContext> optimization_context,
                      std::shared_ptr<OptimizationStrategy> optimization_strategy);

        virtual Id id() const override;
        virtual void cancel() override;
        virtual void wait_until_completed() const override;
        virtual bool wait_until_completed_for(std::chrono::milliseconds interval_ms) const override;
        virtual Status current_status() const override;
        virtual void set_status_listener(StatusListener listener) override;
        virtual std::optional<Solution> latest_solution() const override;
        virtual uint8_t current_progress() const override;
        virtual void set_progress_listener(ProgressListener listener) override;

        virtual void start() override;

      private:
        void notify_status_change();

        Id _id;
        std::shared_ptr<Task> _task;
        std::shared_ptr<OptimizationContext> _optimization_context;
        std::shared_ptr<OptimizationStrategy> _optimization_strategy;
        std::future<void> _done_future;
        std::atomic<Status> _status;
        StatusListener _status_listener; // [TODO] consider thread safety
        std::shared_ptr<assfire::logger::Logger> _logger;
    };
} // namespace assfire::optimizer