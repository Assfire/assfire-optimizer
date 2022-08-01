#include "TaskSignalListenerImpl.hpp"

#include "Exceptions.hpp"
#include "assfire/optimizer/worker/worker.pb.h"

using namespace assfire::messenger;

namespace assfire::optimizer {

    TaskSignal::Type convertSignalType(worker::TaskSignal::Type type) {
        switch (type) {
        case worker::TaskSignal::TASK_SIGNAL_TYPE_START: {
            return TaskSignal::Type::START;
            break;
        }
        case worker::TaskSignal::TASK_SIGNAL_TYPE_CANCEL: {
            return TaskSignal::Type::CANCEL;
            break;
        }
        default: {
            throw IllegalMessageFormat("Unknown signal type");
        }
        }
    }

    TaskSignal TaskSignalListenerImpl::next() {
        std::optional<Message> msg = _message_consumer->next_message();
        if (!msg) { throw MessageStreamClosed("Task signal stream closed unexpectedly"); }
        worker::TaskSignal proto_signal = messenger::unpack<worker::TaskSignal>(msg->payload());
        return TaskSignal(convertSignalType(proto_signal.type()), proto_signal.task_id());
    }

    void TaskSignalListenerImpl::stop() {
        _message_consumer->stop();
    }

} // namespace assfire::optimizer
