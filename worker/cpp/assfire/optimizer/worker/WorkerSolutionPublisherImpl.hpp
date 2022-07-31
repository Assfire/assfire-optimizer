
#pragma once

#include "WorkerSolutionPublisher.hpp"
#include "assfire/messenger/api/Publisher.hpp"

#include <memory>

namespace assfire::optimizer {

    class WorkerSolutionPublisherImpl : public WorkerSolutionPublisher {
      public:
        void publish(const std::string& task_id, Solution solution) override;

      private:
        std::shared_ptr<messenger::Publisher> _publisher;
    };

} // namespace assfire::optimizer