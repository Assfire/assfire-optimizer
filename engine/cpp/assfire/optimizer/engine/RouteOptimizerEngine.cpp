#include "RouteOptimizerEngine.hpp"

#include "BasicOptimizationStrategyProvider.hpp"
#include "DiscardingStateManagerProvider.hpp"
#include "EngineSession.hpp"
#include "InMemorySolutionPublisherProvider.hpp"
#include "LoggingProgressTrackerProvider.hpp"
#include "ProgressTracker.hpp"
#include "SolutionPublisher.hpp"
#include "StateManager.hpp"

namespace assfire::optimizer {

    RouteOptimizerEngine::RouteOptimizerEngine()
        : _optimization_strategy_provider(std::make_shared<BasicOptimizationStrategyProvider>()),
          _solution_publisher_provider(std::make_shared<InMemorySolutionPublisherProvider>()),
          _state_manager_provider(std::make_shared<DiscardingStateManagerProvider>()),
          _progress_tracker_provider(std::make_shared<LoggingProgressTrackerProvider>()) {}

    RouteOptimizerEngine::RouteOptimizerEngine(std::shared_ptr<OptimizationStrategyProvider> optimization_strategy_provider,
                                               std::shared_ptr<SolutionPublisherProvider> solution_publisher_provider,
                                               std::shared_ptr<StateManagerProvider> state_manager_provider,
                                               std::shared_ptr<ProgressTrackerProvider> progress_tracker_provider)
        : _optimization_strategy_provider(optimization_strategy_provider),
          _solution_publisher_provider(solution_publisher_provider),
          _state_manager_provider(state_manager_provider),
          _progress_tracker_provider(progress_tracker_provider) {}

    std::unique_ptr<Session> RouteOptimizerEngine::solve(const Task& task, const OptimizationStrategyId& optimization_strategy_id) const {
        std::shared_ptr<OptimizationStrategy> optimization_strategy =
            _optimization_strategy_provider->get_optimization_strategy(optimization_strategy_id);
        std::shared_ptr<SolutionPublisher> solution_publisher = _solution_publisher_provider->get_solution_publisher(task.id());
        std::shared_ptr<StateManager> state_manager           = _state_manager_provider->get_state_manager(task.id());
        std::shared_ptr<ProgressTracker> progress_tracker     = _progress_tracker_provider->get_progress_tracker(task.id());

        std::shared_ptr<OptimizationContext> optimization_context =
            std::make_shared<OptimizationContext>(solution_publisher, state_manager, progress_tracker);

        std::unique_ptr<EngineSession> session =
            std::make_unique<EngineSession>(std::make_shared<Task>(task), optimization_context, optimization_strategy);

        session->start();

        return session;
    }

} // namespace assfire::optimizer