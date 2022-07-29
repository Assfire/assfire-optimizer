#pragma once

#include "SupervisorChannel.hpp"
#include "Worker.hpp"

#include <memory>
#include <string>

namespace assfire::optimizer {
    class MessageProcessor {
      public:
        MessageProcessor();

        void startProcessingLoop();

      private:
        void process_start_task_message(const Task& task, const OptimizationStrategyId& strategy_id);
        void process_cancel_task_message(const std::string& task_id);
        void send_heartbeat_message();

        std::shared_ptr<Worker> _worker;
        std::shared_ptr<SupervisorChannel> _supervisor_channel;
        std::shared_ptr<logger::Logger> _logger;
    };
} // namespace assfire::optimizer