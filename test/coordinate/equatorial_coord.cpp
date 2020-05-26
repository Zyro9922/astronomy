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
namespace bu = boost::units;

BOOST_AUTO_TEST_SUITE(angle)

    BOOST_AUTO_TEST_CASE(right_ascension) {
        //Create object of Right Ascension
        RightAscension<double, quantity<bud::plane_angle,double>>
                ra(25.0 * bud::degrees);

        //Check value
        BOOST_CHECK_CLOSE(ra.get_angle().value(), 25.0, 0.001);

        //Quantity stored as expected?
        BOOST_TEST((std::is_same<decltype(ra.get_angle()), quantity<bud::plane_angle,double>>::value));
    }

BOOST_AUTO_TEST_SUITE_END()