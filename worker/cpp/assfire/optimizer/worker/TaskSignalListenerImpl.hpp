#pragma once

#include "TaskSignalListener.hpp"
#include "assfire/messenger/api/Consumer.hpp"

#include <memory>

namespace assfire::optimizer {
    class TaskSignalListenerImpl : public TaskSignalListener {
      public:
        virtual TaskSignal next() override;
        virtual void interrupt() override;

      private:
        std::shared_ptr<messenger::Consumer> _message_consumer;
    };
} // namespace assfire::optimizer