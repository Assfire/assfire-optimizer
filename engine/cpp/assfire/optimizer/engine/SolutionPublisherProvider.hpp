#pragma once

#include "assfire/optimizer/api/Session.hpp"
#include "SolutionPublisher.hpp"

#include <memory>

namespace assfire::optimizer {
    class SolutionPublisherProvider {
      public:
        virtual ~SolutionPublisherProvider() = default;

        virtual std::shared_ptr<SolutionPublisher> get_solution_publisher(Session::Id session_id) const = 0;
    };
} // namespace assfire::optimizer