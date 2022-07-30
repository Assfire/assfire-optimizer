#pragma once

#include <stdexcept>

namespace assfire::optimizer {
    class WorkerAlreadyStarted : public std::logic_error {
      public:
        WorkerAlreadyStarted(const char* what) : std::logic_error(what) {}
    };
    class WorkerNotStarted : public std::logic_error {
      public:
        WorkerNotStarted(const char* what) : std::logic_error(what) {}
    };
    class SignalListenerInterrupted : public std::logic_error {
      public:
        SignalListenerInterrupted(const char* what) : std::logic_error(what) {}
    };
} // namespace assfire::optimizer