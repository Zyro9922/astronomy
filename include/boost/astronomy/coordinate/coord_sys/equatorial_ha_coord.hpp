/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_EQUATORIAL_HA_COORD_HPP
#define BOOST_ASTRONOMY_EQUATORIAL_HA_COORD_HPP

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/units/get_dimension.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/units/physical_dimensions/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

namespace boost { namespace astronomy { namespace coordinate {

namespace bu = boost::units;
namespace bg = boost::geometry;

template
<
    typename CoordinateType = double,
    typename HourAngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
    typename Declination = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct equatorial_ha_coord : public coord_sys
    <2, bg::cs::spherical<bg::radian>, CoordinateType>
{
  ///@cond INTERNAL
  BOOST_STATIC_ASSERT_MSG(
      ((std::is_same<typename bu::get_dimension<HourAngleQuantity>::type,
          bu::plane_angle_dimension>::value) &&
       (std::is_same<typename bu::get_dimension<Declination>::type,
           bu::plane_angle_dimension>::value)),
      "Hour Angle and Declination must be of plane angle type");
  BOOST_STATIC_ASSERT_MSG((std::is_floating_point<CoordinateType>::value),
                          "CoordinateType must be a floating-point type");
  ///@endcond
 public:
  typedef HourAngleQuantity quantity1;
  typedef Declination quantity2;

  //Default constructor
  equatorial_ha_coord() {}

  equatorial_ha_coord
      (
          HourAngleQuantity const &Ha,
          Declination const &Dec
      )
  {
    this->set_ha_dec(Ha, Dec);
  }

  //Create tuple of Hour Angle and Declination
  std::tuple<HourAngleQuantity, Declination> get_ha_dec() const
  {
    return std::make_tuple(this->get_ha(), this->get_dec());
  }

  //Get Hour Angle
  HourAngleQuantity get_ha() const
  {
    return static_cast<HourAngleQuantity>
    (
        bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
            (bg::get<0>(this->point))
    );
  }

  //Get Declination
  Declination get_dec() const
  {
    return static_cast<Declination>
    (
        bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
            (bg::get<1>(this->point))
    );
  }

  //Set value of Hour Angle and Declination
  void set_ha_dec
      (
          HourAngleQuantity const &Ha,
          Declination const &Dec
      )
  {
    this->set_ha(Ha);
    this->set_dec(Dec);
  }

  //Set Hour Angle
  void set_ha(HourAngleQuantity const &Ha)
  {
    bg::set<0>
        (
            this->point,
            static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Ha).value()
        );
  }

  //Set Declination
  void set_dec(Declination const &Dec)
  {
    bg::set<1>
        (
            this->point,
            static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Dec).value()
        );
  }

}; //equatorial_ha_coord

//Make Galactic Coordinate
template
    <
        typename CoordinateType,
        template<typename Unit2, typename CoordinateType_> class HourAngleQuantity,
        template<typename Unit1, typename CoordinateType_> class Declination,
        typename Unit1,
        typename Unit2
    >
equatorial_ha_coord
    <
        CoordinateType,
        Declination<Unit1, CoordinateType>,
        HourAngleQuantity<Unit2, CoordinateType>
    > make_equatorial_ha_coord
    (
        HourAngleQuantity<Unit2, CoordinateType> const &Ha,
        Declination<Unit1, CoordinateType> const &Dec
    )
{
  return equatorial_ha_coord
      <
          CoordinateType,
          HourAngleQuantity<Unit2, CoordinateType>,
          Declination<Unit1, CoordinateType>
      > (Ha, Dec);
}

//Print Equatorial Hour Angle Coordinates
template
    <
        typename CoordinateType,
        class HourAngleQuantity,
        class Declination
    >
std::ostream &operator << (std::ostream &out, equatorial_ha_coord
    <CoordinateType, HourAngleQuantity, Declination> const &point) {
  out << "Equatorial Coordinate (Hour Angle: "
      << point.get_ha() << ", Declination: "
      << point.get_dec() << ")";

  return out;
}

}}}

#endif  // BOOST_ASTRONOMY_EQUATORIAL_HA_COORD_HPP
