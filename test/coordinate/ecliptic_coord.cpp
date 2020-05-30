#define BOOST_TEST_MODULE ecliptic_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/ecliptic_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::astronomy::coordinate;
using namespace boost::units;
using namespace boost::units::si;
namespace bud = boost::units::degree;
namespace bu = boost::units;

BOOST_AUTO_TEST_SUITE(ecliptic_coord_constructors)

    BOOST_AUTO_TEST_CASE(ecliptic_coord_default_constructor) {
        ecliptic_coord<
                double,
                quantity<bud::plane_angle>,
                quantity<bud::plane_angle>>
                ec;

        //Check set_EclipticLon_EclipticLat
        ec.set_EclipticLon_EclipticLat(45.0 * bud::degrees, 18.0 * bud::degrees);

        //Check values
        BOOST_CHECK_CLOSE(ec.get_EclipticLon().value(), 45.0, 0.001);
        BOOST_CHECK_CLOSE(ec.get_EclipticLat().value(), 18.0, 0.001);

        //Quantities stored as expected?
        BOOST_TEST((std::is_same<decltype(ec.get_EclipticLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(ec.get_EclipticLat()), quantity<bud::plane_angle>>::value));
    }

    BOOST_AUTO_TEST_CASE(ecliptic_coord_quantities_constructor) {
        //Make Ecliptic Coordinate Check
        auto ec1 = make_ecliptic_coord
                (15.0 * bud::degrees, 39.0 * bud::degrees);

        //Check values
        BOOST_CHECK_CLOSE(ec1.get_EclipticLon().value(), 15.0, 0.001);
        BOOST_CHECK_CLOSE(ec1.get_EclipticLat().value(), 39.0, 0.001);

        //Quantities stored as expected?
        BOOST_TEST((std::is_same<decltype(ec1.get_EclipticLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(ec1.get_EclipticLat()), quantity<bud::plane_angle>>::value));

        //Ecliptic Coordinate constructor
        ecliptic_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
                ec2(1.5 * bud::degrees, 9.0 * bud::degrees);

        //Check values
        BOOST_CHECK_CLOSE(ec2.get_EclipticLon().value(), 1.5, 0.001);
        BOOST_CHECK_CLOSE(ec2.get_EclipticLat().value(), 9.0, 0.001);

        //Quantities stored as expected?
        BOOST_TEST((std::is_same<decltype(ec2.get_EclipticLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(ec2.get_EclipticLat()), quantity<bud::plane_angle>>::value));
    }

BOOST_AUTO_TEST_SUITE_END()
