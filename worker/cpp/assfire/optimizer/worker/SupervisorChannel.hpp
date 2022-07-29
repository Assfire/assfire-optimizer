#pragma once

#include "SupervisorEnvelope.hpp"

#include <chrono>
#include <string>

namespace assfire::optimizer {
    class SupervisorChannel {
      public:
        virtual ~SupervisorChannel() = default;

        virtual SupervisorEnvelope recv(std::chrono::milliseconds timeout) = 0;
        virtual void send(SupervisorEnvelope msg)                          = 0;
    };
} // namespace assfire::optimizer