#include "EngineSession.hpp"

#include "OptimizationError.hpp"
#include "SessionStateError.hpp"

namespace assfire::optimizer {

    EngineSession::EngineSession(std::shared_ptr<Task> task, std::shared_ptr<OptimizationContext> optimization_context,
                                 std::shared_ptr<OptimizationStrategy> optimization_strategy)
        : _task(task),
          _optimization_context(std::move(optimization_context)),
          _optimization_strategy(std::move(optimization_strategy)),
          _status(Status::QUEUED) {}

    void EngineSession::cancel() {
        Status expected_status = Status::IN_PROGRESS;
        if (!_status.compare_exchange_strong(expected_status, Status::CANCELLED)) {
            throw SessionStateError("Trying to cancel optimization session that isn't in progress");
        }
        _optimization_context->interrupt();
        notify_status_change();
    }

    void EngineSession::wait_until_completed() const {
        if (_status == Status::QUEUED) { throw SessionStateError("Optimization session was not started [wait_until_completed_for]"); }
        if (_done_future.valid()) { _done_future.wait(); }
    }

    bool EngineSession::wait_until_completed_for(std::chrono::milliseconds interval_ms) const {
        if (_status == Status::QUEUED) { throw SessionStateError("Optimization session was not started [wait_until_completed]"); }
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
            throw SessionStateError("Trying to double-start optimization session [start]");
        }

        notify_status_change();

        _done_future = std::async(std::launch::async, [&]() {
            try {
                _optimization_strategy->solve(*_task, _optimization_context);
                _status.store(Status::FINISHED);
            } catch (const OptimizationError& e) {
                // [TODO] Log message
                _status.store(Status::FAILED);
                throw;
            } catch (...) {
                // [TODO] Log message
                _status.store(Status::FAILED);
                throw;
            }
            notify_status_change();
        });
    }

    void EngineSession::notify_status_change() {
        if (_status_listener) { _status_listener(_status.load()); }
    }

} // namespace assfire::optimizer
