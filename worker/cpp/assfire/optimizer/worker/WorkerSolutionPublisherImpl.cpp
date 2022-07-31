
#include "WorkerSolutionPublisherImpl.hpp"

#include "assfire/optimizer/worker/worker.pb.h"

namespace assfire::optimizer {

    assfire::api::v1::optimizer::Solution convertSolution(Solution sol) {
        return assfire::api::v1::optimizer::Solution(); // [TODO]
    }

    void WorkerSolutionPublisherImpl::publish(const std::string& task_id, Solution solution) {
        worker::SolutionUpdate update;
        update.set_task_id(task_id);
        update.mutable_solution()->CopyFrom(convertSolution(solution)); // [TODO]
        _publisher->publish(messenger::Message(update));
    }

} // namespace assfire::optimizer
