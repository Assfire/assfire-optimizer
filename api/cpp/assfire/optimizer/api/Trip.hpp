#pragma once

#include "Vehicle.hpp"
#include "Waypoint.hpp"

#include <vector>

namespace assfire::optimizer {
    class Trip {
      public:
        using Waypoints = std::vector<Waypoint>;
        using Cost      = unsigned long;

        Trip() : _vehicle_id(0) {}
        Trip(Vehicle::Id vehicle_id, Waypoints waypoints, Cost cost) : _vehicle_id(vehicle_id), _waypoints(waypoints), _cost(cost) {}
        Trip(const Trip& rhs) = default;
        Trip(Trip&& rhs)      = default;

        Trip& operator=(const Trip& rhs) = default;
        Trip& operator=(Trip&& rhs) = default;

        bool operator==(const Trip& rhs) const = default;

        Vehicle::Id vehicle_id() const {
            return _vehicle_id;
        }
        void set_vehicle_id(Vehicle::Id vehicle_id) {
            _vehicle_id = vehicle_id;
        }

        const Waypoints& waypoints() const {
            return _waypoints;
        }
        void set_waypoints(Waypoints waypoints) {
            _waypoints = std::move(waypoints);
        }

        const Cost& cost() const {
            return _cost;
        }
        void set_cost(Cost cost) {
            _cost = cost;
        }

      private:
        Vehicle::Id _vehicle_id;
        Waypoints _waypoints;
        Cost _cost;
    };
} // namespace assfire::optimizer