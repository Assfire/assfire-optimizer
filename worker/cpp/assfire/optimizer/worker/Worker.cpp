#include "Worker.hpp"

#include "Exceptions.hpp"
#include "assfire/logger/api/LoggerProvider.hpp"

using namespace std::chrono_literals;

namespace assfire::optimizer {
    Worker::Worker(std::shared_ptr<RouteOptimizer> engine, std::shared_ptr<TaskProvider> task_provider,
                   std::shared_ptr<HeartbeatPublisher> heartbeat_publisher, std::shared_ptr<ProgressPublisher> progress_publisher,
                   std::shared_ptr<StatusPublisher> status_publisher, std::shared_ptr<WorkerSolutionPublisher> solution_publisher,
                   std::shared_ptr<TaskSignalListener> task_signal_listener)
        : _state(State::NOT_STARTED),
          _engine(engine),
          _task_provider(task_provider),
          _heartbeat_publisher(heartbeat_publisher),
          _progress_publisher(progress_publisher),
          _status_publisher(status_publisher),
          _solution_publisher(solution_publisher),
          _task_signal_listener(task_signal_listener),
          _logger(logger::LoggerProvider::get("assfire.optimizer.Worker")) {}

    Worker::~Worker() {
        _logger->info("Stopping worker");

        _state = State::INTERRUPTED;
        _logger->info("Stopping accepting new tasks...");

        _logger->info("Waiting for current tasks to finish...");

        _sessions_manager.wait_for_all_sessions_to_complete();

        _state = State::STOPPED;

        _task_signal_listener->stop();

        _work_ftr.wait();

        _logger->info("Worker stopped");
    }

    void Worker::start() {
        _logger->info("Starting worker...");
        State expected_state = State::NOT_STARTED;
        if (!_state.compare_exchange_strong(expected_state, State::STARTED)) {
            _logger->error("Trying to start worker but it's already started");
            throw WorkerAlreadyStarted("Worker is already started or is being interrupted. Double start is not allowed");
        }

        _work_ftr = std::async(std::launch::async, [&] {
            while (_state != State::STOPPED) {
                try {
                    process_signal(_task_signal_listener->next());
                } catch (const SignalListenerInterrupted& e) {
                    _logger->info("Task signal listener is interrupted");
                } catch (const std::exception& e) { _logger->error("Unexpected error while processing task signal: {}", e.what()); }
            }
            _heartbeat_publisher->stop();
            _sessions_manager.clear();
            _logger->info("Worker event-loop is stopped");
        });

        _heartbeat_publisher->start();
        _logger->info("Worker started");
    } // namespace assfire::optimizer

    void Worker::process_signal(const TaskSignal& signal) {
        switch (signal.type()) {
        case TaskSignal::Type::START: {
            if (_state == State::STARTED) {
                start_task(signal.task_id());
            } else {
                _logger->warn("Trying to start task {} while worker is not ready to accept tasks. Task ignored", signal.task_id());
            }
            break;
        }
        case TaskSignal::Type::CANCEL: {
            cancel_task(signal.task_id());
            break;
        }
        case TaskSignal::Type::IGNORE: {
            // Do nothing - useful for tests
            break;
        }
        }
    }

    void Worker::cancel_task(const std::string& task_id) {
        if (_sessions_manager.cancel_session(task_id)) {
            _logger->info("Sent interruption signal to optimization session {} ...", task_id);
        } else {
            _logger->error("Trying to stop task {} that isn't present. Ignoring signal", task_id);
        }
    }

    void Worker::start_task(const std::string& task_id) {
        if (_sessions_manager.contains(task_id)) {
            _logger->error("Trying to start task that is already in progress. Ignoring signal");
        } else {
            _logger->info("Loading task {} ...", task_id);
            WorkerTask task = _task_provider->load(task_id);

            _logger->info("Starting new optimization session {} ...", task_id);

            _sessions_manager.start_session(
                task_id, _engine->solve(task.task(), task.strategy_id(), false),
                [&](Session::ProgressValue p) { _progress_publisher->publish(task_id, p); },
                [&](Session::Status s) { _status_publisher->publish(task_id, s); });
        }
    }

} // namespace assfire::optimizer