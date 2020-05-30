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
namespace bud = boost::units::degree;

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

//Equatorial Coordinate Struct
template
<
    typename CoordinateType = double,
    typename XQuantity = RightAscension<CoordinateType,bu::quantity<bu::si::plane_angle, CoordinateType>>,
    typename DeclinationQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
>
struct equatorial_coord : public coord_sys
    <2, bg::cs::spherical<bg::degree>, CoordinateType>
{
public:
    //Default constructor
    equatorial_coord() {}

    equatorial_coord
    (
        XQuantity const &X,
        DeclinationQuantity const &Declination
    )
    {
        this->set_X_Declination(X, Declination);
    }

    std::tuple<XQuantity, DeclinationQuantity> get_X_Declination() const
    {
        return std::make_tuple(this->get_X(), this->get_Declination());
    }

    XQuantity get_X() const
    {
        XQuantity x = bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                (bg::get<0>(this->point));
        return x;
    }

    DeclinationQuantity get_Declination() const
    {
        return static_cast<DeclinationQuantity>
            (
                bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                        (bg::get<1>(this->point))
            );
    }

    //Set value of X and Declination
    void set_X_Declination
    (
            XQuantity const &X,
            DeclinationQuantity const &Declination
    )
    {
        this->set_X(X);
        this->set_Declination(Declination);
    }

    //Set X
    void set_X(XQuantity const &X)
    {
        bg::set<0>
            (
            this->point,
            (X.get_angle()).value()
            );
    }

    //Set Declination
    void set_Declination(DeclinationQuantity const &Declination)
    {
        bg::set<1>
            (
            this->point,
            static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Declination).value()
            );
    }

}; //equatorial_coord

//Make Equatorial Coordinate
template
<
    typename CoordinateType,
    template<typename CoordinateType_, typename Angle> class XQuantity,
    template<typename Unit2, typename CoordinateType_> class DeclinationQuantity,
    typename Angle,
    typename Unit2
>
equatorial_coord
<
    CoordinateType,
    XQuantity<CoordinateType, Angle>,
    DeclinationQuantity<Unit2, CoordinateType>
> make_equatorial_coord
(
    XQuantity<CoordinateType, Angle> const &X,
    DeclinationQuantity<Unit2, CoordinateType> const &Declination
)
{
    return equatorial_coord
        <
            CoordinateType,
            XQuantity<CoordinateType,Angle>,
            DeclinationQuantity<Unit2, CoordinateType>
        > (X, Declination);
}

//Print Equatorial Coordinates
template
<
    typename CoordinateType,
    class XQuantity,
    class DeclinationQuantity
>
std::ostream &operator<<(std::ostream &out, equatorial_coord
        <CoordinateType, XQuantity, DeclinationQuantity> const &point) {
    out << "Equatorial Coordinate (";
    point.get_X().print();
    out << " , Declination: " << point.get_Declination() << ")";

    return out;
}

}}}

#endif //BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
