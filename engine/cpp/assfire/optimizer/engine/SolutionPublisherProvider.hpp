#pragma once

#include "SolutionPublisher.hpp"

#include <memory>

namespace assfire::optimizer {
    class SolutionPublisherProvider {
      public:
        virtual ~SolutionPublisherProvider() = default;

        virtual std::shared_ptr<SolutionPublisher> get_solution_publisher() = 0;
    };
} // namespace assfire::optimizer