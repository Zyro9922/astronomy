#ifndef BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
#define BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

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

    void print() {
        std::cout << "Right Ascension: " << _ra;
    }

//    TODO: Use SOFA to convert
//    double convert_to_ha()
//    {
//
//    }
};

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

    void print() {
        std::cout << "Hour Angle: " << _ha;
    }

//    TODO: Use SOFA to convert
//    double convert_to_ra()
//    {
//
//    }
};

}}}

#endif //BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
