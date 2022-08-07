#pragma once

#include "HeartbeatPublisher.hpp"
#include "ProgressPublisher.hpp"
#include "StatusPublisher.hpp"
#include "TaskProvider.hpp"
#include "TaskSignalListener.hpp"
#include "WorkerSolutionPublisher.hpp"
#include "SessionsStorage.hpp"
#include "assfire/logger/api/Logger.hpp"
#include "assfire/optimizer/api/RouteOptimizer.hpp"
#include "assfire/optimizer/api/Session.hpp"

#include <atomic>
#include <future>

namespace assfire::optimizer {
    class Worker {
      public:
        enum class State { NOT_STARTED, STARTED, INTERRUPTED, STOPPED };

        Worker(std::shared_ptr<RouteOptimizer> engine, std::shared_ptr<TaskProvider> task_provider,
               std::shared_ptr<HeartbeatPublisher> heartbeat_publisher, std::shared_ptr<ProgressPublisher> progress_publisher,
               std::shared_ptr<StatusPublisher> status_publisher, std::shared_ptr<WorkerSolutionPublisher> solution_publisher,
               std::shared_ptr<TaskSignalListener> task_signal_listener);

        ~Worker();

        void start();
        void stop();

      private:
        void process_signal(const TaskSignal& signal);
        void cancel_task(const std::string& task_id);
        void start_task(const std::string& task_id);

        std::atomic<State> _state;
        std::shared_ptr<RouteOptimizer> _engine;

        std::shared_ptr<TaskProvider> _task_provider;
        std::shared_ptr<HeartbeatPublisher> _heartbeat_publisher;
        std::shared_ptr<ProgressPublisher> _progress_publisher;
        std::shared_ptr<StatusPublisher> _status_publisher;
        std::shared_ptr<WorkerSolutionPublisher> _solution_publisher;
        std::shared_ptr<TaskSignalListener> _task_signal_listener;

        SessionsManager _sessions_manager;

        std::shared_ptr<logger::Logger> _logger;
        std::future<void> _work_ftr;
    };
} // namespace assfire::optimizer