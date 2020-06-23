/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP
#define BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/units/get_dimension.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/units/physical_dimensions/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

/**
 * The plane containing the Earth’s orbit around the Sun is called
 * the ecliptic and the other planets in our Solar System also move
 * in orbits close to this plane.
 *
 * When making calculations on objects in the Solar System it is
 * therefore often convenient to define positions with respect to
 * the ecliptic, that is, to use the ecliptic coordinate system.
 *
 * Ecliptic Latitude
 * The ecliptic plane is extended until it intersects the celestial
 * sphere to create an “ecliptic equator” as the reference point from
 * which Ecliptic Latitudes are measured. The Ecliptic Latitude, denoted
 * by β, is the angular distance that an object P lies above or below the
 * ecliptic plane and falls within the range ±90◦.
 * Latitudes above the ecliptic plane are positive angles while latitudes
 * below the ecliptic plane are negative angles. An object, such as the Sun,
 * whose orbit lies entirely within the ecliptic plane has an ecliptic latitude
 * of 0◦.
 *
 * Ecliptic Longitude
 * The Ecliptic Longitude, designated by λ, measures how far away an object is
 * from the First Point of Aries. The Ecliptic Longitude is in the range [0◦, 360◦]
 * and measured along the ecliptic toward the First Point of Aries.
 */

namespace boost { namespace astronomy { namespace coordinate {

namespace bu = boost::units;
namespace bg = boost::geometry;

template
<
    typename CoordinateType = double,
    typename LatQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
    typename LonQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct ecliptic_coord : public coord_sys
    <2, bg::cs::spherical<bg::radian>, CoordinateType>
{
  ///@cond INTERNAL
  BOOST_STATIC_ASSERT_MSG(
      ((std::is_same<typename bu::get_dimension<LatQuantity>::type,
          bu::plane_angle_dimension>::value) &&
       (std::is_same<typename bu::get_dimension<LonQuantity>::type,
           bu::plane_angle_dimension>::value)),
      "Latitude and Longitude must be of plane angle type");
  BOOST_STATIC_ASSERT_MSG((std::is_floating_point<CoordinateType>::value),
                          "CoordinateType must be a floating-point type");
  ///@endcond
public:
    typedef LatQuantity quantity1;
    typedef LonQuantity quantity2;

    //Default constructor
    ecliptic_coord() {}

    ecliptic_coord
    (
            LatQuantity const &Lat,
            LonQuantity const &Lon
    )
    {
        this->set_lat_lon(Lat, Lon);
    }

    //Create a tuple of Ecliptic Latitude and Ecliptic Longitude
    std::tuple<LatQuantity, LonQuantity> get_lat_lon() const
    {
        return std::make_tuple(this->get_lat(), this->get_lon());
    }

    //Get Ecliptic Latitude
    LatQuantity get_lat() const
    {
        return static_cast<LatQuantity>
        (
            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                    (bg::get<0>(this->point))
        );
    }

    //Get Ecliptic Longitude
    LonQuantity get_lon() const
    {
        return static_cast<LonQuantity>
        (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<1>(this->point))
        );
    }

    //Set value of Ecliptic Latitude and Ecliptic Longitude
    void set_lat_lon
    (
            LatQuantity const &Lat,
            LonQuantity const &Lon
    )
    {
        this->set_lat(Lat);
        this->set_lon(Lon);
    }

    //Set Ecliptic Latitude
    void set_lat(LatQuantity const &Lat)
    {
        bg::set<0>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Lat).value()
            );
    }

    //Set Ecliptic Longitude
    void set_lon(LonQuantity const &Lon)
    {
        bg::set<1>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Lon).value()
            );
    }

}; //ecliptic_coord

//Make Ecliptic Coordinate
template
<
    typename CoordinateType,
    template<typename Unit2, typename CoordinateType_> class LatQuantity,
    template<typename Unit1, typename CoordinateType_> class LonQuantity,
    typename Unit1,
    typename Unit2
>
ecliptic_coord
<
    CoordinateType,
    LatQuantity<Unit2, CoordinateType>,
    LonQuantity<Unit1, CoordinateType>
> make_ecliptic_coord
(
    LatQuantity<Unit2, CoordinateType> const &Lat,
    LonQuantity<Unit1, CoordinateType> const &Lon
)
{
    return ecliptic_coord
        <
            CoordinateType,
            LatQuantity<Unit2, CoordinateType>,
            LonQuantity<Unit1, CoordinateType>
        > (Lat, Lon);
}

//Print Ecliptic Coordinates
template
<
    typename CoordinateType,
    class LatQuantity,
    class LonQuantity
>
std::ostream &operator << (std::ostream &out, ecliptic_coord
        <CoordinateType, LatQuantity, LonQuantity> const &point) {
    out << "Ecliptic Coordinate (Ecliptic Latitude: "
        << point.get_lat() << ", Ecliptic Longitude: "
        << point.get_lon() << ")";

    return out;
}

}}}

#endif //BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP
