#pragma once

#include "assfire/optimizer/api/Solution.hpp"
#include <optional>

namespace assfire::optimizer {
    class SolutionPublisher {
      public:
        virtual ~SolutionPublisher() = default;

        virtual void publish(Solution solution) = 0;

        virtual std::optional<Solution> latest_solution() const = 0;
    };
} // namespace assfire::optimizer