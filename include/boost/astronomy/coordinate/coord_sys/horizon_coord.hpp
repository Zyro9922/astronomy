/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_HORIZON_COORD_HPP
#define BOOST_ASTRONOMY_HORIZON_COORD_HPP

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
 * The Horizon Coordinates, Altitude and Azimuth, of an object
 * in the sky are referred to the plane of the observer’s horizon
 *
 * Azimuth
 * THe Azimuth, is in the range of 0◦ to 360◦ and indicates how far an object
 * in the sky is from the north as measured along an observer’s horizon.
 *
 * Altitude
 * The Altitude, represented by the symbol h, and ranges from −90◦ to +90◦.
 * Positive altitudes indicate objects above the horizon while negative
 * altitudes indicate objects below the horizon.
 *
**/

namespace boost { namespace astronomy { namespace coordinate {

namespace bu = boost::units;
namespace bg = boost::geometry;

template
<
    typename CoordinateType = double,
    typename AltitudeQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
    typename AzimuthQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct horizon_coord : public coord_sys
    <2, bg::cs::spherical<bg::radian>, CoordinateType>
{
  ///@cond INTERNAL
  BOOST_STATIC_ASSERT_MSG(
      ((std::is_same<typename bu::get_dimension<AltitudeQuantity>::type,
          bu::plane_angle_dimension>::value) &&
       (std::is_same<typename bu::get_dimension<AzimuthQuantity>::type,
           bu::plane_angle_dimension>::value)),
      "Altitude and Azimuth must be of plane angle type");
  BOOST_STATIC_ASSERT_MSG((std::is_floating_point<CoordinateType>::value),
                          "CoordinateType must be a floating-point type");
  ///@endcond
public:
    typedef AltitudeQuantity quantity1;
    typedef AzimuthQuantity quantity2;

    //Default constructor
    horizon_coord() {}

    horizon_coord
    (
        AltitudeQuantity const &Altitude,
        AzimuthQuantity const &Azimuth
    )
    {
        this->set_altitude_azimuth(Altitude, Azimuth);
    }

    //Create tuple of Altitude and Azimuth
    std::tuple<AltitudeQuantity, AzimuthQuantity> get_altitude_azimuth() const
    {
        return std::make_tuple(this->get_altitude(), this->get_azimuth());
    }

    //Get Altitude
    AltitudeQuantity get_altitude() const
    {
        return static_cast<AltitudeQuantity>
            (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<0>(this->point))
            );
    }

    //Get Azimuth
    AzimuthQuantity get_azimuth() const
    {
        return static_cast<AzimuthQuantity>
            (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<1>(this->point))
            );
    }

    //Set value of Altitude and Azimuth
    void set_altitude_azimuth
    (
        AltitudeQuantity const &Altitude,
        AzimuthQuantity const &Azimuth
    )
    {
        this->set_altitude(Altitude);
        this->set_azimuth(Azimuth);
    }

    //Set Altitude
    void set_altitude(AltitudeQuantity const &Altitude)
    {
        bg::set<0>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Altitude).value()
            );
    }

    //Set Azimuth
    void set_azimuth(AzimuthQuantity const &Azimuth)
    {
        bg::set<1>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Azimuth).value()
            );
    }

}; //horizon_coord

//Make Horizon Coordinate
template
<
    typename CoordinateType,
    template<typename Unit1, typename CoordinateType_> class AltitudeQuantity,
    template<typename Unit2, typename CoordinateType_> class AzimuthQuantity,
    typename Unit1,
    typename Unit2
>
horizon_coord
<
    CoordinateType,
    AltitudeQuantity<Unit1, CoordinateType>,
    AzimuthQuantity<Unit2, CoordinateType>
> make_horizon_coord
(
    AltitudeQuantity<Unit1, CoordinateType> const &Altitude,
    AzimuthQuantity<Unit2, CoordinateType> const &Azimuth
)
{
    return horizon_coord
        <
            CoordinateType,
            AltitudeQuantity<Unit1, CoordinateType>,
            AzimuthQuantity<Unit2, CoordinateType>
        > (Altitude, Azimuth);
}

//Print Horizon Coordinates
template
<
    typename CoordinateType,
    class AltitudeQuantity,
    class AzimuthQuantity
>
std::ostream &operator << (std::ostream &out, horizon_coord
        <CoordinateType, AltitudeQuantity, AzimuthQuantity> const &point) {
    out << "Horizon Coordinate (Altitude: "
        << point.get_altitude() << ", Azimuth: "
        << point.get_azimuth() << ")";

    return out;
}

}}}

#endif //BOOST_ASTRONOMY_HORIZON_COORD_HPP
