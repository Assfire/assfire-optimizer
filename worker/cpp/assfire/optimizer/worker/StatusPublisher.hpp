#pragma once

#include "assfire/optimizer/api/Session.hpp"

#include <string>

namespace assfire::optimizer {
    class StatusPublisher {
      public:
        virtual ~StatusPublisher() = default;

        virtual void publish(const std::string& task_id, Session::Status status) = 0;
    };
} // namespace assfire::optimizer