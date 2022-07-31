#include "HeartbeatPublisherImpl.hpp"

#include "assfire/optimizer/worker/worker.pb.h"

#include <chrono>

using namespace std::chrono_literals;

namespace assfire::optimizer {
    HeartbeatPublisherImpl::HeartbeatPublisherImpl(std::shared_ptr<messenger::Publisher> publisher, std::chrono::milliseconds publish_interval)
        : _is_interrupted(false),
          _publisher(publisher),
          _publish_interval(publish_interval) {}

    void HeartbeatPublisherImpl::start() {
        _work_ftr = std::async(std::launch::async, [&] {
            while (!_is_interrupted) {
                worker::Heartbeat heartbeat;
                _publisher->publish(messenger::Message(heartbeat));
                std::unique_lock<std::mutex> lck(_mtx);
                _interrupt_var.wait_for(lck, _publish_interval);
            }
            _is_interrupted = false;
        });
    }

    void HeartbeatPublisherImpl::stop() {
        _is_interrupted = true;
        _interrupt_var.notify_all();
    }

} // namespace assfire::optimizer