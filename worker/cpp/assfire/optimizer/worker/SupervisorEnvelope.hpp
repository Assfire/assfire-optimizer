#pragma once

#include <string>

namespace assfire::optimizer {
    class SupervisorEnvelope {
      public:
        enum class MessageType { NOT_INITIALIZED, NEW_TASK, CANCEL_TASK, STATUS_UPDATE, PROGRESS_UPDATE, SOLUTION_UPDATE, WORKER_HEARTBEAT };

        SupervisorEnvelope() = default;
        SupervisorEnvelope(MessageType type, std::string payload) : _type(type), _payload(payload) {}
        SupervisorEnvelope(const SupervisorEnvelope& rhs) = default;
        SupervisorEnvelope(SupervisorEnvelope&& rhs)      = default;

        SupervisorEnvelope& operator=(const SupervisorEnvelope& rhs) = default;
        SupervisorEnvelope& operator=(SupervisorEnvelope&& rhs) = default;

        MessageType type() const {
            return _type;
        }

        const std::string& payload() const {
            return _payload;
        }

      private:
        MessageType _type = MessageType::NOT_INITIALIZED;
        std::string _payload;
    };
} // namespace assfire::optimizer