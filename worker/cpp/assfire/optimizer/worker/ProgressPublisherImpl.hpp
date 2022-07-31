#pragma once

#include "ProgressPublisher.hpp"
#include "assfire/messenger/api/Publisher.hpp"

#include <memory>

namespace assfire::optimizer {

    class ProgressPublisherImpl : public ProgressPublisher {
      public:
        void publish(const std::string& task_id, Session::ProgressValue progress) override;

      private:
        std::shared_ptr<messenger::Publisher> _publisher;
    };

} // namespace assfire::optimizer