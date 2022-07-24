#pragma once

#include <string>
#include "GeoPoint.hpp"
#include "TransportProfileId.hpp"

namespace assfire::optimizer {
    class Vehicle {
        public:
            using Id = unsigned long;

            Vehicle() : _id(0){}
            Vehicle(Id id, GeoPoint start_location, GeoPoint end_location, TransportProfileId transport_profile_id) :
            _id(id),
            _start_location(std::move(start_location)),
            _end_location(std::move(end_location)),
            _transport_profile_id(std::move(transport_profile_id))
            {}
            Vehicle(const Vehicle& rhs) = default;
            Vehicle(Vehicle &&rhs) = default;

            Vehicle& operator=(const Vehicle& rhs) = default;
            Vehicle& operator=(Vehicle&& rhs) = default;

            bool operator==(const Vehicle& rhs) const = default;

            Id id() const {return _id;}
            void set_id(Id id) {_id = id;}

            const GeoPoint& start_location() const {return _start_location;}
            void set_start_location(GeoPoint start_location) {_start_location = std::move(start_location);}

            const GeoPoint& end_location() const {return _end_location;}
            void set_end_location(GeoPoint end_location) {_end_location = std::move(end_location);}

            const TransportProfileId& transport_profile_id() const {return _transport_profile_id;}
            void set_transport_profile_id(TransportProfileId transport_profile_id) {_transport_profile_id = std::move(transport_profile_id);}

        private:
            Id _id;
            GeoPoint _start_location;
            GeoPoint _end_location;
            TransportProfileId _transport_profile_id;
    }
}