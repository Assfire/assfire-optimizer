#pragma once

#include "StatusPublisher.hpp"
#include "assfire/messenger/api/Publisher.hpp"

#include <memory>

namespace assfire::optimizer {
    class StatusPublisherImpl : public StatusPublisher {
      public:
        virtual void publish(const std::string& task_id, Session::Status status) override;

      private:
        std::shared_ptr<messenger::Publisher> _publisher;
    };
} // namespace assfire::optimizer