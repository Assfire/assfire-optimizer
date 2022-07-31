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

    class MessageStreamClosed : public std::runtime_error {
      public:
        MessageStreamClosed(const char* what) : std::runtime_error(what) {}
    };

    class IllegalMessageFormat : public std::runtime_error {
      public:
        IllegalMessageFormat(const char* what) : std::runtime_error(what) {}
    };

    class UnsupportedStatus : public std::invalid_argument {
      public:
        UnsupportedStatus(const char* what) : std::invalid_argument(what) {}
    };
} // namespace assfire::optimizer