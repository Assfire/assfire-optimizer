#pragma once

#include "assfire/optimizer/api/Session.hpp"

namespace assfire::optimizer {
    class ProgressPublisher {
      public:
        virtual ~ProgressPublisher() = default;

        virtual void publish(const std::string& task_id, Session::ProgressValue progress) = 0;
    };
} // namespace assfire::optimizer