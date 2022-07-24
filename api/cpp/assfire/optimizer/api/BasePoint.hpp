#pragma once
#include "GeoPoint.hpp"
#include "TimeWindow.hpp"

#include <vector>

namespace assfire::optimizer {
    class BasePoint {
      public:
        enum class Type { HOTEL };

        enum class CostModel { PER_DAY };

        using Id          = unsigned long;
        using TimeWindows = std::vector<TimeWindow>;
        using Duration    = long;
        using Cost        = long;

        BasePoint() : _id(0), _visit_duration(0), _visit_cost(0) {}

        BasePoint(Id id, TimeWindows time_windows, GeoPoint geo_point, Duration visit_duration, Cost visit_cost)
            : _id(id),
              _time_windows(std::move(time_windows)),
              _geo_point(std::move(geo_point)),
              _visit_duration(visit_duration),
              _visit_cost(visit_cost) {}

        BasePoint(const BasePoint& rhs) = default;
        BasePoint(BasePoint&& rhs)      = default;

        BasePoint& operator=(const BasePoint& rhs) = default;
        BasePoint& operator=(BasePoint&& rhs) = default;

        bool operator==(const BasePoint& rhs) const = default;

        Id id() const {
            return _id;
        }
        void set_id(Id id) {
            _id = id;
        }

        const TimeWindows& time_windows() const {
            return _time_windows;
        }
        void set_time_windows(TimeWindows time_windows) {
            _time_windows = std::move(time_windows);
        }

        const GeoPoint& geo_point() const {
            return _geo_point;
        }
        void set_geo_point(GeoPoint gp) {
            _geo_point = std::move(gp);
        }

        Duration visit_duration() const {
            return _visit_duration;
        }
        void set_visit_duration(Duration visit_duration) {
            _visit_duration = visit_duration;
        }

        Cost visit_cost() const {
            return _visit_cost;
        }
        void set_visit_cost(Cost visit_cost) {
            _visit_cost = visit_cost;
        }

        std::string to_string() const {
            std::string result("<");
            result += std::to_string(_id);
            result += ">";
            return result;
        }

      private:
        Id _id;
        TimeWindows _time_windows;
        GeoPoint _geo_point;
        Duration _visit_duration;
        Cost _visit_cost;
    };
} // namespace assfire::optimizer