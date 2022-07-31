#include "WorkerSolutionPublisherProvider.hpp"

#include <mutex>

namespace assfire::optimizer {

    class WorkerSolutionPublisherEngineInterface : public SolutionPublisher {
      public:
        WorkerSolutionPublisherEngineInterface(std::string task_id, std::shared_ptr<WorkerSolutionPublisher> publisher)
            : _task_id(std::move(task_id)),
              _solution_publisher(std::move(publisher)) {}

        virtual void publish(Solution solution) override {
            _solution_publisher->publish(_task_id, solution);
            std::lock_guard lck(_mtx);
            _latest_solution = solution;
        }

        virtual std::optional<Solution> latest_solution() const override {
            std::lock_guard lck(_mtx);
            return _latest_solution;
        }

      private:
        mutable std::mutex _mtx;
        std::string _task_id;
        std::shared_ptr<WorkerSolutionPublisher> _solution_publisher;
        std::optional<Solution> _latest_solution;
    };

    std::shared_ptr<SolutionPublisher> WorkerSolutionPublisherProvider::get_solution_publisher(Session::Id session_id) const {
        return std::make_shared<WorkerSolutionPublisherEngineInterface>(session_id, _solution_publisher);
    }

} // namespace assfire::optimizer
