#pragma once

namespace assfire::optimizer {
    class HeartbeatPublisher {
      public:
        virtual ~HeartbeatPublisher() = default;

        virtual void start() = 0;
        virtual void stop()  = 0;
    };
} // namespace assfire::optimizer