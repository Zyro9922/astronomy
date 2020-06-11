/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE galactic_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/astronomy/coordinate/coord_sys/galactic_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::units;
using namespace boost::units::si;
using namespace boost::astronomy::coordinate;

namespace bud = boost::units::degree;

BOOST_AUTO_TEST_SUITE(galactic_coord_constructors)

BOOST_AUTO_TEST_CASE(galactic_coord_default_constructor) {
    galactic_coord<
            double,
            quantity<bud::plane_angle>,
            quantity<bud::plane_angle>>
            gc;

    //Check set_lat_lon
        gc.set_lat_lon(45.0 * bud::degrees, 18.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(gc.get_lat().value(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(gc.get_lon().value(), 18.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(gc.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(gc.get_lon()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(galactic_coord_quantities_constructor) {
    //Make Galactic Coordinate Check
    auto gc1 = make_galactic_coord
            (15.0 * bud::degrees, 39.0 * bud::degrees);
    BOOST_CHECK_CLOSE(gc1.get_lat().value(), 15.0, 0.001);
    BOOST_CHECK_CLOSE(gc1.get_lon().value(), 39.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(gc1.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(gc1.get_lon()), quantity<bud::plane_angle>>::value));

    //Galactic Coordinate constructor
    galactic_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
            gc2(1.5 * bud::degrees, 9.0 * bud::degrees);
    BOOST_CHECK_CLOSE(gc2.get_lat().value(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(gc2.get_lon().value(), 9.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(gc2.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(gc2.get_lon()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()
