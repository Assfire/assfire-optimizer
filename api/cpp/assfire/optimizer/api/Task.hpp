#pragma once

#include "BasePoint.hpp"
#include "OptimizationStrategyId.hpp"
#include "Order.hpp"
#include "Vehicle.hpp"

#include <vector>

namespace assfire::optimizer {
    class Task {
      public:
        using Id         = std::string;
        using Orders     = std::vector<Order>;
        using BasePoints = std::vector<BasePoint>;
        using Vehicles   = std::vector<Vehicle>;

        Task() = default;
        Task(Id id, Orders orders, BasePoints base_points, Vehicles vehicles, OptimizationStrategyId optimization_strategy_id)
            : _id(id),
              _orders(std::move(orders)),
              _base_points(std::move(base_points)),
              _vehicles(std::move(vehicles)) {}

        Task(const Task& rhs) = default;
        Task(Task&& rhs)      = default;

        Task& operator=(const Task& rhs) = default;
        Task& operator=(Task&& rhs) = default;

        bool operator==(const Task& rhs) const = default;

        const Id& id() const {
            return _id;
        }

        void set_id(Id id) {
            _id = std::move(id);
        }

        const Orders& orders() const {
            return _orders;
        }
        void set_orders(Orders orders) {
            _orders = std::move(orders);
        }

        const BasePoints& base_points() const {
            return _base_points;
        }
        void set_base_points(BasePoints base_points) {
            _base_points = std::move(base_points);
        }

        const Vehicles& vehicles() const {
            return _vehicles;
        }
        void set_vehicles(Vehicles vehicles) {
            _vehicles = std::move(vehicles);
        }

      private:
        Id _id;
        Orders _orders;
        BasePoints _base_points;
        Vehicles _vehicles;
    };
} // namespace assfire::optimizer