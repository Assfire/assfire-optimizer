#pragma once

namespace assfire::optimizer {
    class HeartbeatPublisher {
      public:
        virtual ~HeartbeatPublisher() = default;

        virtual void on_task_started()  = 0;
        virtual void on_task_finished() = 0;

        virtual void start() = 0;
        virtual void stop()  = 0;
    };
} // namespace assfire::optimizer