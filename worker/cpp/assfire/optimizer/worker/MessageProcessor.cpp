#include "MessageProcessor.hpp"

#include "Exceptions.hpp"
#include "assfire/logger/api/LoggerProvider.hpp"

using namespace std::chrono_literals;

namespace assfire::optimizer {

    MessageProcessor::MessageProcessor() : _logger(logger::LoggerProvider::get("assfire.optimizer.MessageProcessor")) {}

    void MessageProcessor::startProcessingLoop() {
        while (true) {
            SupervisorEnvelope envelope;
            try {
                envelope = _supervisor_channel->recv(15s);
            } catch (const SupervisorChannelTimeout& e) {
                _logger->info("Sending heartbeat to supervisor service...");
                // send_heartbeat_message
                continue;
            } catch (...) {
                _logger->error("Unexpected error on waiting for message from supervisor");
                continue;
            }

            switch (envelope.type()) {
            case SupervisorEnvelope::MessageType::NEW_TASK: {
                // process_start_task_message
                break;
            }
            case SupervisorEnvelope::MessageType::CANCEL_TASK: {
                // process_cancel_task_message
                break;
            }
            default: {
                // Not a supervisor -> server message
                break;
            }
            }
        }
    }

    void MessageProcessor::process_start_task_message(const Task& task, const OptimizationStrategyId& strategy_id) {
        try {
            _worker->process(
                task, strategy_id, [](auto) {}, [](auto) {});
        } catch (const TaskAlreadyInProgress& e) {
            // Send error
        } catch (...) {
            // Send error
        }
    }

    void MessageProcessor::process_cancel_task_message(const std::string& task_id) {
        try {
            _worker->cancel(task_id);
        } catch (const TaskNotFound& e) {
            // Send error
        } catch (const TaskMismatched& e) {
            // Send error
        } catch (...) {
            // Send error
        }
    }

    void MessageProcessor::send_heartbeat_message() {
        _supervisor_channel->send(SupervisorEnvelope(SupervisorEnvelope::MessageType::WORKER_HEARTBEAT, {}));
    }

} // namespace assfire::optimizer