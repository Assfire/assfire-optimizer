#pragma once

#include <stdexcept>

namespace assfire::optimizer {
    class SessionStateError : public std::logic_error {
      public:
        SessionStateError(const std::string& what) : std::logic_error(what) {}
    };
} // namespace assfire::optimizer