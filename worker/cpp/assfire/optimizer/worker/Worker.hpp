#pragma once

#include "assfire/logger/api/Logger.hpp"
#include "assfire/optimizer/api/RouteOptimizer.hpp"
#include "assfire/optimizer/api/Session.hpp"

#include <mutex>

namespace assfire::optimizer {
    class Worker {
      public:
        Worker(std::shared_ptr<RouteOptimizer> engine);

        void process(const Task& task, const OptimizationStrategyId& optimization_strategy_id, Session::StatusListener status_listener,
                     Session::ProgressListener progress_listener);
        void cancel(const std::string& task_id);

      private:
        std::mutex _mtx;
        std::shared_ptr<RouteOptimizer> _engine;
        std::shared_ptr<Session> _current_session;
        std::shared_ptr<logger::Logger> _logger;
    };
} // namespace assfire::optimizer