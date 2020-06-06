#define BOOST_TEST_MODULE horizon_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/astronomy/coordinate/coord_sys/horizon_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::units;
using namespace boost::units::si;
using namespace boost::astronomy::coordinate;

namespace bud = boost::units::degree;

BOOST_AUTO_TEST_SUITE(horizon_coord_constructors)

BOOST_AUTO_TEST_CASE(horizon_coord_default_constructor) {
    horizon_coord<
            double,
            quantity<bud::plane_angle>,
            quantity<bud::plane_angle>>
            hc;

    //Check set_Altitude_Azimuth
    hc.set_Altitude_Azimuth(45.0 * bud::degrees, 18.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc.get_Altitude().value(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(hc.get_Azimuth().value(), 18.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc.get_Altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc.get_Azimuth()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(horizon_coord_quantities_constructor) {
    //Make Horizon Coordinate Check
    auto hc1 = make_horizon_coord
            (15.0 * bud::degrees, 39.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc1.get_Altitude().value(), 15.0, 0.001);
    BOOST_CHECK_CLOSE(hc1.get_Azimuth().value(), 39.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc1.get_Altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc1.get_Azimuth()), quantity<bud::plane_angle>>::value));

    //Horizon Coord constructor
    horizon_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
            hc2(1.5 * bud::degrees, 9.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc2.get_Altitude().value(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(hc2.get_Azimuth().value(), 9.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc2.get_Altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc2.get_Azimuth()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()
