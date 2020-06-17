/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
#define BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

/**
 * The Equatorial Coordinates, are referred to the plane of the Earth’s equator
 *
 * Declination
 * Declination is analogous to latitude and indicates how far away an object is
 * from the celestial equator. Declination is int the range ±90◦ with positive
 * angles indicating locations north of the celestial equator and negative angles
 * indicating locations south of the celestial equator. Because declination is
 * measured with respect to the celestial equator, and the celestial equator’s
 * location does not vary with time of day or an observer’s location, declination
 * for an object is fixed and does not vary with the time of day or an
 * observer’s location.
 *
 * Right Ascension
 * Right ascension is analogous to longitude and indicates how far an object is away
 * from the First Point of Aries, which is the point used to define a celestial prime meridian.
 * It measures the distance from an object to the celestial prime meridian. As with declination,
 * right ascension does not vary with time of day or an observer’s location because it is measured
 * with respect to a fixed location (the First Point of Aries).
 *
 * Hour Angle
 * If we use an observer’s meridian instead of the celestial prime meridian as a reference point,
 * we have another way to measure “celestial longitude" called “hour angle” (H). While right ascension
 * is an angular measurement (although expressed in HMS format) of an object’s distance from the First
 * Point of Aries, hour angle is very much a time measurement. The hour angle for an object is a measure
 * of how long it has been since the object crossed an observer’s meridian.
 * Because of the way that an hour angle is defined (i.e., relative to an observer’s local celestial meridian),
 * it varies both with time of day and an observer’s location.
 *
**/

namespace boost { namespace astronomy { namespace coordinate {

namespace bu = boost::units;
namespace bg = boost::geometry;

//Right Ascension
template
<
    typename CoordinateType = double,
    typename RightAscensionQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct RightAscension {
private:
    RightAscensionQuantity _ra;
public:
    RightAscension(){
        _ra = 0.0 * bu::si::radian;
    };

    RightAscension(RightAscensionQuantity const& ra) : _ra(ra) {}

    RightAscensionQuantity get_angle() const{
        return static_cast<RightAscensionQuantity>(_ra);
    }

//    TODO: Use SOFA to convert
//    double convert_to_ha()
//    {
//
//    }
};

// Left Shift ( << ) overload for Right Ascension
template
<
    typename CoordinateType,
    typename RightAscensionQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
std::ostream& operator << (std::ostream &out, RightAscension<CoordinateType, RightAscensionQuantity> const& ra)
{
    return out << "Right Ascension: " << ra.get_angle();
}

//Hour Angle
template
<
    typename CoordinateType = double,
    typename HourAngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct HourAngle {
private:
    HourAngleQuantity _ha;
public:
    HourAngle(){
        _ha = 0.0 * bu::si::radian;
    }

    HourAngle(HourAngleQuantity const& ha) : _ha(ha) {}

    HourAngleQuantity get_angle() const{
        return static_cast<HourAngleQuantity>(_ha);
    }

//    TODO: Use SOFA to convert
//    double convert_to_ra()
//    {
//
//    }
};

// Left Shift ( << ) overload for Hour Angle
template
<
    typename CoordinateType,
    typename HourAngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
std::ostream& operator << (std::ostream &out, HourAngle<CoordinateType, HourAngleQuantity> const& ha)
{
    return out << "Hour Angle: " << ha.get_angle();
}

//Equatorial Coordinate Struct
template
<
    typename CoordinateType = double,
    typename AngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
    typename LatQuantity = RightAscension<CoordinateType, AngleQuantity>,
    typename DeclinationQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct equatorial_coord : public coord_sys
    <2, bg::cs::spherical<bg::radian>, CoordinateType>
{
public:
    //Default constructor
    equatorial_coord() {}

    equatorial_coord
    (
        LatQuantity const &Lat,
        DeclinationQuantity const &Declination
    )
    {
        this->set_lat_dec(Lat, Declination);
    }

    std::tuple<LatQuantity, DeclinationQuantity> get_lat_dec() const
    {
        return std::make_tuple(this->get_lat(), this->get_dec());
    }

    // Get Latitude
    LatQuantity get_lat() const
    {
        LatQuantity lat =
            static_cast<AngleQuantity>
            (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<0>(this->point))
            );

        return lat;
    }

    // Get Declination
    DeclinationQuantity get_dec() const
    {
        return static_cast<DeclinationQuantity>
            (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<1>(this->point))
            );
    }

    //Set value of Latitude and Declination
    void set_lat_dec
    (
        LatQuantity const &Lat,
        DeclinationQuantity const &Dec
    )
    {
        this->set_lat(Lat);
        this->set_dec(Dec);
    }

    //Set Latitude
    void set_lat(LatQuantity const &Lat)
    {
        bg::set<0>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Lat.get_angle()).value()
            );
    }

    //Set Declination
    void set_dec(DeclinationQuantity const &Dec)
    {
        bg::set<1>
            (
                this->point,
                static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Dec).value()
            );
    }

}; //equatorial_coord

//Make Equatorial Coordinate
template
<
    typename CoordinateType,
    template<typename Unit1, typename CoordinateType_> class AngleQuantity,
    template<typename CoordinateType_, typename AngleQuantity_> class LatQuantity,
    template<typename Unit2, typename CoordinateType_> class DeclinationQuantity,
    typename Unit1,
    typename Unit2
>
equatorial_coord
<
    CoordinateType,
    AngleQuantity<Unit1, CoordinateType>,
    LatQuantity<CoordinateType, AngleQuantity<Unit1, CoordinateType>>,
    DeclinationQuantity<Unit2, CoordinateType>
> make_equatorial_coord
(
    LatQuantity<CoordinateType, AngleQuantity<Unit1, CoordinateType>> const &Lat,
    DeclinationQuantity<Unit2, CoordinateType> const &Dec
)
{
    return equatorial_coord
        <
            CoordinateType,
            AngleQuantity<Unit1, CoordinateType>,
            LatQuantity<CoordinateType,AngleQuantity<Unit1, CoordinateType>>,
            DeclinationQuantity<Unit2, CoordinateType>
        > (Lat, Dec);
}

//Print Equatorial Coordinates
template
<
    typename CoordinateType,
    class AngleQuantity,
    class LatQuantity,
    class DeclinationQuantity
>
std::ostream &operator<<(std::ostream &out, equatorial_coord
        <CoordinateType, AngleQuantity, LatQuantity, DeclinationQuantity> const &point) {
    out << "Equatorial Coordinate ("
    << point.get_lat()
    << ", Declination: " << point.get_dec() << ")";

    return out;
}

}}}

#endif //BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
