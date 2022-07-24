#pragma once

#include "Session.hpp"
#include "Task.hpp"

namespace assfire::optimizer {
    class RouteOptimizer {
        public:
        virtual ~RouteOptimizer() = default;
            virtual std::unique_ptr<Session> solve(const Task& task) = 0;
    };
}