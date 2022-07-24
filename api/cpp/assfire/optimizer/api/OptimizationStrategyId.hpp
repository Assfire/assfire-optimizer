#pragma once

#include <string>

namespace assfire::optimization {
    class OptimizationStrategyId {
        public:
            OptimizationStrategyId() = default;
            explicit OptimizationStrategyId(std::string value) : _value(std::move(value)){}
            OptimizationStrategyId(const OptimizationStrategyId& rhs) = default;
            OptimizationStrategyId(OptimizationStrategyId &&rhs) = default;

            OptimizationStrategyId& operator=(const OptimizationStrategyId& rhs) = default;
            OptimizationStrategyId& operator-(OptimizationStrategyId&& rhs) = default;

            bool operator==(const OptimizationStrategyId& rhs) = default;

            const std::string& value() const {return _value;}

        private:
            std::string _value;
    };
}