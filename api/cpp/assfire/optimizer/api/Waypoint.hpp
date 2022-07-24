#pragma once

#include "Order.hpp"
#include "TimeWindow.hpp"

namespace assfire::optimizer {
    class Waypoint {
      public:
        enum class State { PLANNED, STARTED, FINISHED };

        Waypoint() : _order_id(0), _state(State::PLANNED) {}
        Waypoint(Order::Id order_id, TimeWindow visit_time, State state) : _order_id(order_id), _visit_time(std::move(visit_time)), _state(state) {}
        Waypoint(const Waypoint& rhs) = default;
        Waypoint(Waypoint&& rhs)      = default;

        Waypoint& operator=(const Waypoint& rhs) = default;
        Waypoint& operator=(Waypoint&& rhs) = default;

        bool operator==(const Waypoint& rhs) const = default;

        Order::Id order_id() const {
            return _order_id;
        }
        void set_order_id(Order::Id order_id) {
            _order_id = order_id;
        }

        const TimeWindow& visit_time() const {
            return _visit_time;
        }
        void set_visit_time(TimeWindow visit_time) {
            _visit_time = std::move(visit_time);
        }

        State state() const {
            return _state;
        }
        void set_state(State state) {
            _state = state;
        }

        bool is_started() const {
            return state() == State::STARTED || is_finished();
        }

        bool is_finished() const {
            return state() == State::FINISHED;
        }

      private:
        Order::Id _order_id;
        TimeWindow _visit_time;
        State _state;
    };
} // namespace assfire::optimizer