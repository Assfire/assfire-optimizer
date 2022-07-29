#include "EngineSession.hpp"

#include "OptimizationError.hpp"
#include "SessionStateError.hpp"
#include "assfire/logger/api/LoggerProvider.hpp"

namespace assfire::optimizer {

    EngineSession::EngineSession(std::shared_ptr<Task> task, std::shared_ptr<OptimizationContext> optimization_context,
                                 std::shared_ptr<OptimizationStrategy> optimization_strategy)
        : _id(task->id()),
          _task(task),
          _optimization_context(std::move(optimization_context)),
          _optimization_strategy(std::move(optimization_strategy)),
          _status(Status::QUEUED),
          _logger(assfire::logger::LoggerProvider::get("assfire.optimizer.EngineSession")) {}

    Session::Id EngineSession::id() const {
        return _id;
    }

    void EngineSession::cancel() {
        Status expected_status = Status::IN_PROGRESS;
        if (!_status.compare_exchange_strong(expected_status, Status::CANCELLED)) {
            _logger->error("Trying to cancel session {} but it wasn't started", _id);
            throw SessionStateError("Trying to cancel optimization session that isn't in progress");
        }
        _optimization_context->interrupt();
        notify_status_change();
    }

    void EngineSession::wait_until_completed() const {
        if (_status == Status::QUEUED) {
            _logger->error("Trying to wait until session {} completed but it wasn't yet started", _id);
            throw SessionStateError("Optimization session was not started [wait_until_completed_for]");
        }
        if (_done_future.valid()) { _done_future.wait(); }
    }

    bool EngineSession::wait_until_completed_for(std::chrono::milliseconds interval_ms) const {
        if (_status == Status::QUEUED) {
            _logger->error("Trying to wait until session {} completed but it wasn't yet started", _id);
            throw SessionStateError("Optimization session was not started [wait_until_completed]");
        }
        if (_done_future.valid()) {
            std::future_status status = _done_future.wait_for(interval_ms);
            if (status == std::future_status::timeout) { return false; }
        }
        return true;
    }

    Session::Status EngineSession::current_status() const {
        return _status;
    }

    void EngineSession::set_status_listener(StatusListener listener) {
        listener(current_status());
        _status_listener = listener;
    }

    void EngineSession::set_progress_listener(ProgressListener listener) {
        _optimization_context->progress_tracker().set_progress_listener(listener);
    }

    std::optional<Solution> EngineSession::latest_solution() const {
        return _optimization_context->latest_solution();
    }

    uint8_t EngineSession::current_progress() const {
        return _optimization_context->current_progress();
    }

    void EngineSession::start() {
        // [TODO] Better thread management

        Status expected_status = Status::QUEUED;
        if (!_status.compare_exchange_strong(expected_status, Status::IN_PROGRESS)) {
            _logger->info("Trying to double-start session {}. This isn't allowed", _id);
            throw SessionStateError("Trying to double-start optimization session [start]");
        }

        _logger->info("Starting session {}", _id);

        notify_status_change();

        _done_future = std::async(std::launch::async, [&]() {
            try {
                _optimization_strategy->solve(*_task, _optimization_context);
                expected_status = Status::IN_PROGRESS;
                if (_status.compare_exchange_strong(expected_status, Status::FINISHED)) {
                    // [TODO] Could be cancelled
                    notify_status_change();

                    _logger->info("Session {} successfully finished", _id);
                };
            } catch (const OptimizationError& e) {
                _logger->error("Session {} crashed unexpectedly", _id);
                _status.store(Status::FAILED);
                notify_status_change();
                throw;
            } catch (...) {
                _logger->error("Session {} crashed unexpectedly", _id);
                _status.store(Status::FAILED);
                notify_status_change();
                throw;
            }
        });
    }

    void EngineSession::notify_status_change() {
        if (_status_listener) { _status_listener(current_status()); }
    }

} // namespace assfire::optimizer
