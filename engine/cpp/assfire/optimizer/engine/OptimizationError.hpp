#pragma once

#include <stdexcept>

namespace assfire::optimizer {
    class OptimizationError : public std::runtime_error {
    };
} // namespace assfire::optimization