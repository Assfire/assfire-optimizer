#pragma once

#include "BasePoint.hpp"
#include "Order.hpp"
#include "Vehicle.hpp"
#include "OptimizationStrategyId.hpp"

#include <vector>

namespace assfire::optimizer {
    class Task {
      public:
        using Orders     = std::vector<Order>;
        using BasePoints = std::vector<BasePoint>;
        using Vehicles   = std::vector<Vehicle>;

        Task() = default;
        Task(Orders orders, BasePoints base_points, Vehicles vehicles, OptimizationStrategyId optimization_strategy_id)
            : _orders(std::move(orders)),
              _base_points(std::move(base_points)),
              _vehicles(std::move(vehicles)),
              _optimization_strategy_id(std::move(optimization_strategy_id)) {}

        Task(const Task& rhs) = default;
        Task(Task&& rhs)      = default;

        Task& operator=(const Task& rhs) = default;
        Task& operator=(Task&& rhs) = default;

        bool operator==(const Task& rhs) const = default;

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

        const OptimizationStrategyId& optimization_strategy_id() const {
            return _optimization_strategy_id;
        }
        void set_optimization_strategy_id(OptimizationStrategyId optimization_strategy_id) {
            _optimization_strategy_id = std::move(optimization_strategy_id);
        }

      private:
        Orders _orders;
        BasePoints _base_points;
        Vehicles _vehicles;
        OptimizationStrategyId _optimization_strategy_id;
    };
} // namespace assfire::optimizer