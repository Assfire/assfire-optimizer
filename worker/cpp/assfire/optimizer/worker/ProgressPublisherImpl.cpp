
#include "ProgressPublisherImpl.hpp"

#include "assfire/optimizer/worker/worker.pb.h"

namespace assfire::optimizer {

    void ProgressPublisherImpl::publish(const std::string& task_id, Session::ProgressValue progress) {
        worker::ProgressUpdate update;
        update.set_new_progress(progress);
        _publisher->publish(messenger::Message(update));
    }

} // namespace assfire::optimizer