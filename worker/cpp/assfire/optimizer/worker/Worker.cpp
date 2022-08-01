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

          _solution_publisher(solution_publisher),
          _task_signal_listener(task_signal_listener),
          _logger(logger::LoggerProvider::get("assfire.optimizer.Worker")) {}

    void Worker::start() {
        _logger->info("Starting worker...");
        State expected_state = State::NOT_STARTED;
        if (!_state.compare_exchange_strong(expected_state, State::STARTED)) {
            _logger->error("Trying to start worker while it's still in active state");
            throw WorkerAlreadyStarted("Worker is already started or is being interrupted. Double start is not allowed");
        }

        _work_ftr = std::async(std::launch::async, [&] {
            while (_state != State::INTERRUPTED) {
                try {
                    TaskSignal signal = _task_signal_listener->next();

                    cleanup_sessions();

                    switch (signal.type()) {
                    case TaskSignal::Type::START: {
                        auto iter = _active_sessions.find(signal.task_id());
                        if (iter != _active_sessions.end()) {
                            _logger->error("Trying to start task that is already in progress. Ignoring signal");
                        } else {
                            _logger->info("Loading task {} ...", signal.task_id());
                            WorkerTask task = _task_provider->load(signal.task_id());

                            _logger->info("Starting new optimization session {} ...", signal.task_id());
                            std::shared_ptr<Session> session = _engine->solve(task.task(), task.strategy_id(), false);
                            session->set_progress_listener([&](Session::ProgressValue p) { _progress_publisher->publish(signal.task_id(), p); });
                            session->set_status_listener([&](Session::Status s) { _status_publisher->publish(signal.task_id(), s); });
                            session->start();
                            _active_sessions.emplace(signal.task_id(), session);
                        }
                        break;
                    }
                    case TaskSignal::Type::CANCEL: {
                        auto iter = _active_sessions.find(signal.task_id());
                        if (iter == _active_sessions.end()) {
                            _logger->error("Trying to stop task {} that isn't present. Ignoring signal", signal.task_id());
                        } else {
                            _logger->info("Interrupting optimization session {} ...", signal.task_id());
                            iter->second->cancel();
                        }
                        break;
                    }
                    }
                } catch (const SignalListenerInterrupted& e) {
                    _logger->info("Task signal listener is interrupted");
                } catch (const std::exception& e) { _logger->error("Unexpected error while processing task signal: {}", e.what()); }
            }
            _heartbeat_publisher->stop();
            wait_for_sessions_to_complete();
            _active_sessions.clear();
            _state = State::NOT_STARTED;
            _logger->info("Worker event-loop is stopped");
        });

        _heartbeat_publisher->start();
    }

    void Worker::stop() {
        _logger->info("Stopping worker");

        State expected_state = State::STARTED;
        if (!_state.compare_exchange_strong(expected_state, State::INTERRUPTED)) {
            _logger->error("Trying to interrupt worker while it's not in active state or is already being interrupted");
            throw WorkerNotStarted("Worker is not started or is already being interrupted. Double start is not allowed");
        }

        _logger->info("Stopping accepting new tasks...");

        _task_signal_listener->stop();

        _logger->info("Waiting for current tasks to finish...");

        _work_ftr.wait();

        _logger->info("Worker stopped");
    }

    void Worker::cleanup_sessions() {
        for (auto it = _active_sessions.begin(); it != _active_sessions.end();) {
            if (it->second->is_in_terminal_state()) {
                it = _active_sessions.erase(it);
            } else {
                ++it;
            }
        }
    }

    void Worker::wait_for_sessions_to_complete() {
        for (const auto& p : _active_sessions) {
            p.second->wait_until_completed();
        }
    }

} // namespace assfire::optimizer