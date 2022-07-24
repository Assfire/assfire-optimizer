#pragma once

#include <cstdint>
#include <string>

namespace assfire::optimizer
{
    /**
     * \brief This class represents geographic location denoted by latitude and longitude
     */
    class GeoPoint
    {
    public:
        using FixedPointCoordinate = std::int32_t;

        /**
         * \brief Construct a new Geo Point object representing coordinates (0, 0)
         *
         */
        GeoPoint() = default;

        /**
         * \brief Construct a new Geo Point object representing coordinates encoded using fixed point integet format with 6 decimal places, e.g. coordinates (53.3456, 65.23456) are represented as (53345600, 65234560).
         *
         * \param lat latitude encoded in fixed point integer format with 6 decimal places
         * \param lon longitude encoded in fixed point integer format with 6 decimal places
         */
        GeoPoint(FixedPointCoordinate lat, FixedPointCoordinate lon) : _lat(lat),
                                                                       _lon(lon) {}
        /**
         * \brief Construct a new Geo Point object representing coordinates encoded using floating point format, e.g. (53.3456, 65.23456)
         *
         * \param lat latitude encoded in floating point format
         * \param lon longitude encoded in floating point format
         */
        GeoPoint(double lat, double lon) : _lat((FixedPointCoordinate)(lat * 1e6)),
                                           _lon((FixedPointCoordinate)(lon * 1e6)) {}
        GeoPoint(const GeoPoint &rhs) = default;
        GeoPoint(GeoPoint &&rhs) = default;

        GeoPoint operator+(const GeoPoint &rhs) const
        {
            GeoPoint result(*this);
            result += rhs;
            return result;
        }

        GeoPoint &operator+=(const GeoPoint &rhs)
        {
            _lat += rhs._lat;
            _lon += rhs._lon;
            return *this;
        }

        GeoPoint operator-(const GeoPoint &rhs) const
        {
            GeoPoint result(*this);
            result -= rhs;
            return result;
        }

        GeoPoint &operator-=(const GeoPoint &rhs)
        {
            _lat -= rhs._lat;
            _lon -= rhs._lon;
            return *this;
        }

        GeoPoint operator*(double v) const
        {
            GeoPoint result(*this);
            result *= v;
            return result;
        }

        GeoPoint &operator*=(double v)
        {
            _lat *= v;
            _lon *= v;
            return *this;
        }

        GeoPoint operator/(double v) const
        {
            GeoPoint result(*this);
            result /= v;
            return result;
        }

        GeoPoint &operator/=(double v)
        {
            _lat /= v;
            _lon /= v;
            return *this;
        }

        GeoPoint &operator=(const GeoPoint &rhs) = default;
        GeoPoint &operator=(GeoPoint &&rhs) = default;
        bool operator==(const GeoPoint &rhs) const = default;
        bool operator!=(const GeoPoint &rhs) const = default;

        FixedPointCoordinate lat() const
        {
            return _lat;
        }

        FixedPointCoordinate lon() const
        {
            return _lon;
        }

        void set_lat(FixedPointCoordinate lat)
        {
            _lat = lat;
        }

        void set_lon(FixedPointCoordinate lon)
        {
            _lon = lon;
        }

        double lat_double() const
        {
            return _lat / 1e6;
        }

        double lon_double() const
        {
            return _lon / 1e6;
        }

        void set_lat(double lat)
        {
            _lat = (FixedPointCoordinate) (lat * 1e6);
        }

        void set_lon(double lon)
        {
            _lon = (FixedPointCoordinate) (lon * 1e6);
        }

        /**
         * \brief Formats string representation of geo point using fixed point integer format with 6 decimal places
         *
         * \return std::string string representation of geo point
         */
        std::string to_string() const
        {
            std::string result("(");
            result += std::to_string(_lat);
            result += ", ";
            result += std::to_string(_lon);
            result += ")";
            return result;
        }

        /**
         * \brief Formats string representation of geo point using floating point coordinates format
         *
         * \return std::string string representation of geo point
         */
        std::string to_float_string() const
        {
            std::string result("(");
            result += std::to_string(_lat / 1e6);
            result += ", ";
            result += std::to_string(_lon / 1e6);
            result += ")";
            return result;
        }

    private:
        FixedPointCoordinate _lat;
        FixedPointCoordinate _lon;
    };
}