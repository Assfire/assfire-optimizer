#pragma once

#include "WorkerSolutionPublisher.hpp"
#include "assfire/optimizer/engine/SolutionPublisherProvider.hpp"

#include <memory>

namespace assfire::optimizer {
    class WorkerSolutionPublisherProvider : public SolutionPublisherProvider {
      public:
        virtual std::shared_ptr<SolutionPublisher> get_solution_publisher(Session::Id session_id) const override;

      private:
        std::shared_ptr<WorkerSolutionPublisher> _solution_publisher;
    };
} // namespace assfire::optimizer