#define BOOST_TEST_MODULE galactic_coord_test

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/galactic_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::astronomy::coordinate;
using namespace boost::units;
using namespace boost::units::si;
namespace bud = boost::units::degree;
namespace bu = boost::units;

BOOST_AUTO_TEST_SUITE(galactic_coord_constructors)

    BOOST_AUTO_TEST_CASE(galactic_coord_default_constructor)
    {
        galactic_coord<
                double,
                quantity<bud::plane_angle>,
                quantity<bud::plane_angle>>
                gc;

        //Check set_GLon_GLat
        gc.set_GLon_GLat(45.0 * bud::degrees, 18.0 * bud::degrees);

        BOOST_CHECK_CLOSE(gc.get_GLon().value(),45.0,0.001);
        BOOST_CHECK_CLOSE(gc.get_GLat().value(),18.0,0.001);

        BOOST_TEST((std::is_same<decltype(gc.get_GLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(gc.get_GLat()), quantity<bud::plane_angle>>::value));

    }

    BOOST_AUTO_TEST_CASE(galactic_coord_quantities_constructor)
    {
        //Make Galactic Coordinate Check
        auto gc1 = make_galactic_coord
                (15.0 * bud::degrees, 39.0 * bud::degrees);
        BOOST_CHECK_CLOSE(gc1.get_GLon().value(), 15.0, 0.001);
        BOOST_CHECK_CLOSE(gc1.get_GLat().value(), 39.0, 0.001);

        //Quantity stored as expected?
        BOOST_TEST((std::is_same<decltype(gc1.get_GLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(gc1.get_GLat()), quantity<bud::plane_angle>>::value));

        //Galactic Coordinate constructor
        galactic_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
                gc2(1.5 * bud::degrees, 9.0 * bud::degrees);
        BOOST_CHECK_CLOSE(gc2.get_GLon().value(), 1.5, 0.001);
        BOOST_CHECK_CLOSE(gc2.get_GLat().value(), 9.0, 0.001);

        //Quantity stored as expected?
        BOOST_TEST((std::is_same<decltype(gc2.get_GLon()), quantity<bud::plane_angle>>::value));
        BOOST_TEST((std::is_same<decltype(gc2.get_GLat()), quantity<bud::plane_angle>>::value));
    }

BOOST_AUTO_TEST_SUITE_END()

