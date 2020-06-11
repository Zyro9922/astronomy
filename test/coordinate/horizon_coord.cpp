/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

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

    //Check set_altitude_azimuth
    hc.set_altitude_azimuth(45.0 * bud::degrees, 18.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc.get_altitude().value(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(hc.get_azimuth().value(), 18.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc.get_altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc.get_azimuth()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(horizon_coord_quantities_constructor) {
    //Make Horizon Coordinate Check
    auto hc1 = make_horizon_coord
            (15.0 * bud::degrees, 39.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc1.get_altitude().value(), 15.0, 0.001);
    BOOST_CHECK_CLOSE(hc1.get_azimuth().value(), 39.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc1.get_altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc1.get_azimuth()), quantity<bud::plane_angle>>::value));

    //Horizon Coord constructor
    horizon_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
            hc2(1.5 * bud::degrees, 9.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(hc2.get_altitude().value(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(hc2.get_azimuth().value(), 9.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(hc2.get_altitude()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(hc2.get_azimuth()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()
