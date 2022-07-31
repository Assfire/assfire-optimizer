
#pragma once

#include "HeartbeatPublisher.hpp"
#include "assfire/messenger/api/Publisher.hpp"

#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>

namespace assfire::optimizer {

    class HeartbeatPublisherImpl : public HeartbeatPublisher {
      public:
        HeartbeatPublisherImpl(std::shared_ptr<messenger::Publisher> publisher,
                               std::chrono::milliseconds publish_interval = std::chrono::seconds(30));
        void start() override;
        void stop() override;

        void set_publish_interval(const std::chrono::milliseconds &publish_interval) {
            _publish_interval = publish_interval;
        }

      private:
        std::atomic_bool _is_interrupted;
        std::shared_ptr<messenger::Publisher> _publisher;
        std::chrono::milliseconds _publish_interval;
        std::future<void> _work_ftr;
        std::mutex _mtx;
        std::condition_variable _interrupt_var;
    };

} // namespace assfire::optimizer