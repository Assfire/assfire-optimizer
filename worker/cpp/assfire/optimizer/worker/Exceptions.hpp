#pragma once

#include <stdexcept>

namespace assfire::optimizer {
    class TaskAlreadyInProgress : public std::logic_error {
      public:
        TaskAlreadyInProgress(const char* what) : std::logic_error(what) {}
    };

    class TaskNotFound : public std::logic_error {
      public:
        TaskNotFound(const char* what) : std::logic_error(what) {}
    };

    class TaskMismatched : public std::logic_error {
      public:
        TaskMismatched(const char* what) : std::logic_error(what) {}
    };

    class SupervisorChannelTimeout : public std::logic_error {
      public:
        SupervisorChannelTimeout(const char* what) : std::logic_error(what) {}
    };
} // namespace assfire::optimizer