#pragma once

#include "ProgressTracker.hpp"
#include "SolutionPublisher.hpp"
#include "StateManager.hpp"

#include <atomic>
#include <functional>
#include <memory>

namespace assfire::optimizer {
    class OptimizationContext {
      public:
        OptimizationContext(std::shared_ptr<SolutionPublisher> solution_publisher, std::shared_ptr<StateManager> state_manager,
                            std::shared_ptr<ProgressTracker> progress_tracker)
            : _solution_publisher(std::move(solution_publisher)),
              _state_manager(std::move(state_manager)),
              _progress_tracker(std::move(progress_tracker)),
              _is_interrupted(false) {}

        const SolutionPublisher& solution_publisher() const {
            return *_solution_publisher;
        }

        SolutionPublisher& solution_publisher() {
            return *_solution_publisher;
        }

        void publish_solution(const Solution& solution) {
            _solution_publisher->publish(solution);
        }

        std::optional<Solution> latest_solution() const {
            return _solution_publisher->latest_solution();
        }

        const StateManager& state_manager() const {
            return *_state_manager;
        }

        StateManager& state_manager() {
            return *_state_manager;
        }

        void save_state(uint32_t size, StateManager::StateProvider provide_state) {
            _state_manager->save(size, std::move(provide_state));
        }

        void load_state(StateManager::StateConsumer consume_state) const {
            _state_manager->load(std::move(consume_state));
        }

        const ProgressTracker& progress_tracker() const {
            return *_progress_tracker;
        }

        ProgressTracker& progress_tracker() {
            return *_progress_tracker;
        }

        void set_current_progress(uint8_t progress) {
            _progress_tracker->set_progress(progress);
        }

        uint8_t current_progress() const {
            return _progress_tracker->progress();
        }

        bool is_interrupted() const {
            return _is_interrupted;
        }

        void interrupt() {
            _is_interrupted.store(true);
        }

      private:
        std::shared_ptr<SolutionPublisher> _solution_publisher;
        std::shared_ptr<StateManager> _state_manager;
        std::shared_ptr<ProgressTracker> _progress_tracker;
        std::atomic_bool _is_interrupted;
    };
} // namespace assfire::optimizer