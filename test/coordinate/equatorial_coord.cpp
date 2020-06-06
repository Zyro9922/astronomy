
#define BOOST_TEST_MODULE equatorial_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/equatorial_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::astronomy::coordinate;
using namespace boost::units;
using namespace boost::units::si;
namespace bud = boost::units::degree;

BOOST_AUTO_TEST_SUITE(angle)

BOOST_AUTO_TEST_CASE(right_ascension)
{
    //Create object of Right Ascension
    RightAscension<double, quantity<bud::plane_angle>>
            ra(25.0 * bud::degrees);

    //Check value
    BOOST_CHECK_CLOSE(ra.get_angle().value(), 25.0, 0.001);

    //Quantity stored as expected?
    BOOST_TEST((std::is_same<decltype(ra.get_angle()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(hour_angle)
{
    //Create object of Hour Angle
    HourAngle<double, quantity<bud::plane_angle>>
            ha(25.0 * bud::degrees);

    //Check value
    BOOST_CHECK_CLOSE(ha.get_angle().value(), 25.0, 0.001);

    //Quantity stored as expected?
    BOOST_TEST((std::is_same<decltype(ha.get_angle()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(equatorial_coord_constructors)

BOOST_AUTO_TEST_CASE(equatorial_coord_default_right_ascension_constructor)
{
    equatorial_coord<double,
            RightAscension<double, quantity<si::plane_angle>>,
            quantity<bud::plane_angle>>
            e;

    //Create object of Right Ascension
    RightAscension<double, quantity<si::plane_angle>>
            ra(25.0 * si::radian);

    //Check value
    BOOST_CHECK_CLOSE(ra.get_angle().value(), 25.0, 0.001);

    //Quantity stored as expected?
    BOOST_TEST((std::is_same<decltype(ra.get_angle()), quantity<si::plane_angle>>::value));

    //Check set_X_Declination
    e.set_X_Declination(ra,39.0 * bud::degree);

    BOOST_CHECK_CLOSE(e.get_X().get_angle().value(),25.0,0.001);
    BOOST_CHECK_CLOSE(e.get_Declination().value(),39.0,0.001);

    BOOST_TEST((std::is_same<decltype(e.get_X().get_angle()), quantity<si::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(e.get_Declination()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()
