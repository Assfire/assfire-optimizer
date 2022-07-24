#pragma once

#include <vector>
#include "Trip.hpp"

namespace assfire::optimizer {
    class Solution {
        public:
            using Trips = std::vector<Trip>;

            Solution() = default;
            Solution(Trips trips, Trip::Cost cost) : _trips(std::move(trips)), _cost(cost){}
            Solution(const Solution& rhs) = default;
            Solution(Solution &&rhs) = default;

            Solution& operator=(const Solution& rhs) = default;
            Solution& operator=(Solution &&rhs) = default;

            bool operator==(const Solution& rhs) const = default;

            const Trips& trips() const {return _trips;}
            void set_trips(Trips trips) {_trips = trips;}

            const Trip::Cost& cost() const {return _cost;}
            void set_cost(Cost cost) {_cost = cost;}

        private:
            Trips _trips;
            Trip::Cost _cost;
    };
}