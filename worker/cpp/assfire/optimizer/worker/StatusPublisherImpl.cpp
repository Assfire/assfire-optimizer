#include "StatusPublisherImpl.hpp"

#include "Exceptions.hpp"
#include "assfire/optimizer/worker/worker.pb.h"

namespace assfire::optimizer {

    namespace {
        assfire::api::v1::optimizer::SolutionStatus convertStatus(Session::Status status) {
            switch (status) {
            case Session::Status::QUEUED: return assfire::api::v1::optimizer::SOLUTION_STATUS_QUEUED;
            case Session::Status::CANCELLED: return assfire::api::v1::optimizer::SOLUTION_STATUS_CANCELLED;
            case Session::Status::FAILED: return assfire::api::v1::optimizer::SOLUTION_STATUS_FAILED;
            case Session::Status::IN_PROGRESS: return assfire::api::v1::optimizer::SOLUTION_STATUS_IN_PROGRESS;
            case Session::Status::FINISHED: return assfire::api::v1::optimizer::SOLUTION_STATUS_FINISHED;
            default: throw UnsupportedStatus("Unsupported status");
            }
        }
    } // namespace

    void StatusPublisherImpl::publish(const std::string& task_id, Session::Status status) {
        worker::StatusUpdate update;
        update.set_new_status(convertStatus(status));
        _publisher->publish(messenger::Message(update));
    }

} // namespace assfire::optimizer
