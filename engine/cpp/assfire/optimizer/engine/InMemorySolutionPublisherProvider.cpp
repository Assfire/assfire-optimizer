#include "InMemorySolutionPublisherProvider.hpp"

#include <mutex>

namespace assfire::optimizer {

    class InMemorySolutionPublisher : public SolutionPublisher {
      public:
        virtual void publish(Solution solution) override {
            std::lock_guard<std::recursive_mutex> guard(mtx);
            _stored_solution = solution;
        }
        virtual std::optional<Solution> latest_solution() override {
            std::lock_guard<std::recursive_mutex> guard(mtx);
            return _stored_solution;
        }

      private:
        std::recursive_mutex mtx;
        std::optional<Solution> _stored_solution;
    };

    std::shared_ptr<SolutionPublisher> InMemorySolutionPublisherProvider::get_solution_publisher(Session::Id session_id) const {
        return std::make_shared<InMemorySolutionPublisher>();
    }

} // namespace assfire::optimizer
