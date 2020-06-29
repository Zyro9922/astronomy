/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_GALACTIC_COORD_HPP
#define BOOST_ASTRONOMY_GALACTIC_COORD_HPP

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
 * To describe the relationships between stars or other celestial
 * objects within our own Galaxy is convenient to use the Galactic
 * Coordinate System.
 *
 * The center of our Milky Way is chosen to be the coordinate system’s
 * origin. The equatorial coordinates for the center of the Milky Way
 * for the standard epoch 1950.0 are right ascension 17h42m and
 * declination −28◦45′.
 *
 * Galactic Latitude
 * The plane containing the Sun and the center of the Milky Way is
 * extended until it intersects the celestial sphere to form a
 * “galactic equator.”
 * Galactic latitudes, denoted by b, are measured with respect to
 * this galactic equator. Galactic latitudes are in the range of ±90◦
 * with positive angles being north of the galactic plane and negative
 * angles being south of the galactic plane.
 *
 * Galactic Longitude
 * Galactic longitudes, denoted by l, are measured counterclockwise so as
 * to increase from 0◦ to 360◦ in the same direction as increasing
 * right ascension.
**/

namespace boost { namespace astronomy { namespace coordinate {

namespace bu = boost::units;
namespace bg = boost::geometry;

template
<
    typename CoordinateType = double,
    typename LatQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
    typename LonQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct galactic_coord : public coord_sys
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
    galactic_coord() {}

    galactic_coord
    (
        LatQuantity const &Lat,
        LonQuantity const &Lon
    )
    {
        this->set_lat_lon(Lat, Lon);
    }

    //Create tuple of Galactic Latitude and Galactic Longitude
    std::tuple<LatQuantity, LonQuantity> get_lat_lon() const
    {
        return std::make_tuple(this->get_lat(), this->get_lon());
    }

    //Get Galactic Latitude
    LatQuantity get_lat() const
    {
        return static_cast<LatQuantity>
        (
            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                    (bg::get<0>(this->point))
        );
    }

    //Get Galactic Longitude
    LonQuantity get_lon() const
    {
        return static_cast<LonQuantity>
        (
            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                    (bg::get<1>(this->point))
        );
    }

    //Set value of Galactic Latitude and Galactic Longitude
    void set_lat_lon
    (
        LatQuantity const &Lat,
        LonQuantity const &Lon
    )
    {
        this->set_lat(Lat);
        this->set_lon(Lon);
    }

    //Set Galactic Latitude
    void set_lat(LatQuantity const &Lat)
    {
        bg::set<0>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Lat).value()
            );
    }

    //Set Galactic Longitude
    void set_lon(LonQuantity const &Lon)
    {
        bg::set<1>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Lon).value()
            );
    }

}; //galactic_coord

//Make Galactic Coordinate
template
<
    typename CoordinateType,
    template<typename Unit2, typename CoordinateType_> class LatQuantity,
    template<typename Unit1, typename CoordinateType_> class LonQuantity,
    typename Unit1,
    typename Unit2
>
galactic_coord
<
    CoordinateType,
    LonQuantity<Unit1, CoordinateType>,
    LatQuantity<Unit2, CoordinateType>
> make_galactic_coord
(
        LatQuantity<Unit2, CoordinateType> const &Lat,
        LonQuantity<Unit1, CoordinateType> const &Lon
)
{
    return galactic_coord
        <
            CoordinateType,
            LatQuantity<Unit2, CoordinateType>,
            LonQuantity<Unit1, CoordinateType>
        > (Lat, Lon);
}

//Print Galactic Coordinates
template
<
    typename CoordinateType,
    class LatQuantity,
    class LonQuantity
>
std::ostream &operator << (std::ostream &out, galactic_coord
        <CoordinateType, LatQuantity, LonQuantity> const &point) {
    out << "Galactic Coordinate (Galactic Latitude: "
        << point.get_lat() << ", Galactic Longitude: "
        << point.get_lon() << ")";

    return out;
}

}}}

#endif //BOOST_ASTRONOMY_GALACTIC_COORD_HPP
