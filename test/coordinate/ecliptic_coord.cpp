/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE ecliptic_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/astronomy/coordinate/coord_sys/ecliptic_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::units;
using namespace boost::units::si;
using namespace boost::astronomy::coordinate;

namespace bud = boost::units::degree;

BOOST_AUTO_TEST_SUITE(ecliptic_coord_constructors)

BOOST_AUTO_TEST_CASE(ecliptic_coord_default_constructor) {
    ecliptic_coord<
            double,
            quantity<bud::plane_angle>,
            quantity<bud::plane_angle>>
            ec;

    //Check set_lat_lon
        ec.set_lat_lon(45.0 * bud::degrees, 18.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(ec.get_lat().value(), 45.0, 0.001);
    BOOST_CHECK_CLOSE(ec.get_lon().value(), 18.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(ec.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(ec.get_lon()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(ecliptic_coord_quantities_constructor) {
    //Make Ecliptic Coordinate Check
    auto ec1 = make_ecliptic_coord
            (15.0 * bud::degrees, 39.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(ec1.get_lat().value(), 15.0, 0.001);
    BOOST_CHECK_CLOSE(ec1.get_lon().value(), 39.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(ec1.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(ec1.get_lon()), quantity<bud::plane_angle>>::value));

    //Ecliptic Coordinate constructor
    ecliptic_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
            ec2(1.5 * bud::degrees, 9.0 * bud::degrees);

    //Check values
    BOOST_CHECK_CLOSE(ec2.get_lat().value(), 1.5, 0.001);
    BOOST_CHECK_CLOSE(ec2.get_lon().value(), 9.0, 0.001);

    //Quantities stored as expected?
    BOOST_TEST((std::is_same<decltype(ec2.get_lat()), quantity<bud::plane_angle>>::value));
    BOOST_TEST((std::is_same<decltype(ec2.get_lon()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()
