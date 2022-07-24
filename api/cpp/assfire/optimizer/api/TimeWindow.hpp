#pragma once

#include <string>
#include <cassert>
#include <chrono>

namespace assfire::optimizer {
    class TimeWindow {
        public:
            using Timestamp = unsigned long long;
            using Width = decltype(Timestamp() - Timestamp());

            TimeWindow() = default;
            TimeWindow(Timestamp start, Timestamp end) : _start(start), _end(end) {}
            TimeWindow(const TimeWindow& rhs) = default;
            TimeWindow(TimeWindow&& rhs) = default;

            TimeWindow& operator=(const TimeWindow& rhs) = default;
            TimeWindow& operator=(TimeWindow&& rhs) = default;

            bool operator==(const TimeWindow& rhs) const = default;

            Timestamp start() const {return _start;}
            Timestamp end() const {return _end;}
            void set_start(Timestamp value) {_start = value;}
            void set_end(Timestamp value) {_end = value;}

            bool contains(Timestamp time_point) const {
                return time_point >= start() && time_point <= end();
            }

            Width width() const {
                assert(_end >= _start);
                return _end - _start;
            }

            std::string to_string() {
                return "";
            }

        private:
            Timestamp _start = 0;
            Timestamp _end = 0;
    };
}