#include "Worker.hpp"

#include "Exceptions.hpp"
#include "assfire/logger/api/LoggerProvider.hpp"

using namespace std::chrono_literals;

namespace assfire::optimizer {
    Worker::Worker(std::shared_ptr<RouteOptimizer> engine) : _engine(engine), _logger(logger::LoggerProvider::get("assfire.optimizer.Worker")) {}

    void Worker::process(const Task& task, const OptimizationStrategyId& optimization_strategy_id, Session::StatusListener status_listener,
                         Session::ProgressListener progress_listener) {
        {
            std::lock_guard<std::mutex> guard(_mtx);
            if (_current_session && !_current_session->is_in_terminal_state()) {
                _logger->error("Can't start processing new task {} because another task {} is already in progress", task.id(),
                               _current_session->id());
                throw TaskAlreadyInProgress("Another task is already being processed by worker");
            }
            _logger->info("Starting processing task {}", task.id());
            _current_session = _engine->solve(task, optimization_strategy_id, false);
        }

        _current_session->set_progress_listener(std::move(progress_listener));
        _current_session->set_status_listener(std::move(status_listener));

        _current_session->start();
    }

    void Worker::cancel(const std::string& task_id) {
        std::lock_guard<std::mutex> guard(_mtx);

        if (!_current_session) {
            _logger->error("Can't cancel task {} because it isn't found", task_id);
            throw TaskNotFound("Trying to cancel non-existent task");
        }
        if (_current_session->id() != task_id) {
            _logger->error("Can't cancel task {} because it isn't found. Another task {} is currently in progress", task_id, _current_session->id());
            throw TaskMismatched("Trying to cancel non-existent task");
        }

        _logger->info("Cancelling task {}", task_id);
        _current_session->cancel();
        while (!_current_session->wait_until_completed_for(5s)) {
            _logger->warn("Task {} is still not finished. Waiting for its completion...");
        }
    }
} // namespace assfire::optimizer