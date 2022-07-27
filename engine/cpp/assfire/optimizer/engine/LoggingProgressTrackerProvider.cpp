#include "LoggingProgressTrackerProvider.hpp"

#include "ProgressTracker.hpp"

#include <atomic>

namespace assfire::optimizer {

    class LoggingProgressTracker : public ProgressTracker {
      public:
        LoggingProgressTracker(Session::Id session_id) : _session_id(session_id), _current_progress(0) {}

        virtual void set_progress(uint8_t percent) override {
            // [TODO] Logging
            _current_progress = percent;
            if (_progress_listener) { _progress_listener(_current_progress); }
        }

        virtual uint8_t progress() const override {
            return _current_progress;
        }

        virtual void set_progress_listener(ProgressListener listener) override {
            _progress_listener = listener;
        }

      private:
        Session::Id _session_id;
        std::atomic_int8_t _current_progress;
        ProgressListener _progress_listener; // [TODO] Thread safety
    };

    std::shared_ptr<ProgressTracker> LoggingProgressTrackerProvider::get_progress_tracker(Session::Id session_id) const {
        return std::make_shared<LoggingProgressTracker>(session_id);
    }

} // namespace assfire::optimizer
