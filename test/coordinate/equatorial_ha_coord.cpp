/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE equatorial_ha_coord

#include <iostream>
#include <boost/units/io.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/astronomy/coordinate/coord_sys/equatorial_ha_coord.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost::units;
using namespace boost::units::si;
using namespace boost::astronomy::coordinate;

namespace bud = boost::units::degree;

BOOST_AUTO_TEST_SUITE(equatorial_ha_coord_constructors)

BOOST_AUTO_TEST_CASE(equatorial_ha_coord_default_constructor) {
  equatorial_ha_coord<
      double,
      quantity<bud::plane_angle>,
      quantity<bud::plane_angle>>
      eha;

  //Check set_ha_dec
  eha.set_ha_dec(45.0 * bud::degrees, 18.0 * bud::degrees);

  //Check values
  BOOST_CHECK_CLOSE(eha.get_ha().value(), 45.0, 0.001);
  BOOST_CHECK_CLOSE(eha.get_dec().value(), 18.0, 0.001);

  //Quantities stored as expected?
  BOOST_TEST((std::is_same<decltype(eha.get_ha()), quantity<bud::plane_angle>>::value));
  BOOST_TEST((std::is_same<decltype(eha.get_dec()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_CASE(equatorial_ha_coord_quantities_constructor) {
  //Make Equatorial Coordinate Check
  auto eha1 = make_equatorial_ha_coord
      (15.0 * bud::degrees, 39.0 * bud::degrees);
  BOOST_CHECK_CLOSE(eha1.get_ha().value(), 15.0, 0.001);
  BOOST_CHECK_CLOSE(eha1.get_dec().value(), 39.0, 0.001);

  //Quantities stored as expected?
  BOOST_TEST((std::is_same<decltype(eha1.get_ha()), quantity<bud::plane_angle>>::value));
  BOOST_TEST((std::is_same<decltype(eha1.get_dec()), quantity<bud::plane_angle>>::value));

  //Equatorial Coordinate constructor
  equatorial_ha_coord<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>>
      eha2(1.5 * bud::degrees, 9.0 * bud::degrees);
  BOOST_CHECK_CLOSE(eha2.get_ha().value(), 1.5, 0.001);
  BOOST_CHECK_CLOSE(eha2.get_dec().value(), 9.0, 0.001);

  //Quantities stored as expected?
  BOOST_TEST((std::is_same<decltype(eha2.get_ha()), quantity<bud::plane_angle>>::value));
  BOOST_TEST((std::is_same<decltype(eha2.get_dec()), quantity<bud::plane_angle>>::value));
}

BOOST_AUTO_TEST_SUITE_END()


