#pragma once

#include "SolutionPublisherProvider.hpp"

namespace assfire::optimizer {
    class InMemorySolutionPublisherProvider : public SolutionPublisherProvider {
      public:
        virtual std::shared_ptr<SolutionPublisher> get_solution_publisher(Session::Id session_id) const override;
    };
} // namespace assfire::optimizer