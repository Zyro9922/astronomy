/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MODULE time_conversions_test

#include <iostream>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/astronomy/time/time_conversions.hpp>
#include <boost/astronomy/time/parser.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(time_conversions)

BOOST_AUTO_TEST_CASE(time)
{
  //Make an object of universal time
  //What was the GST at 14h 36m 51.67s UT on Greenwich date 22 April 1980?
  //GST = 4h 40m 5.23s
  //Verified from Practical Astronomy with your Calculator
  //by Peter Duffett-Smith
  std::string ts1("1980-04-22 14:36:51.67");
  ptime t1(time_from_string(ts1));

  DecimalHours d1 = GST(t1);

  BOOST_CHECK_CLOSE(d1.get_hours(), 4, 0.5);
  BOOST_TEST(abs(d1.get_minutes() - 40) <= 10);
  BOOST_TEST(d1.get_seconds() >= 0);
  BOOST_TEST(d1.get_seconds() <= 60);

  //What is the local sidereal time on the longitude 64◦ W
  //when the GST is 4h 40m 5.23s OR
  //at 14h 36m 51.67s UT on Greenwich date 22 April 1980
  // Local Sidereal Time at Longitude 64.00°(W) = 0h 24m 05s
  DecimalHours d2 = LST(64,DIRECTION::WEST,d1.get());

  BOOST_CHECK_CLOSE(d2.get_hours(), 0, 0.5);
  BOOST_TEST(abs(d2.get_minutes() - 24) <= 10);
  BOOST_TEST(d2.get_seconds() >= 0);
  BOOST_TEST(d2.get_seconds() <= 60);

  //What was the GST at 19h 21m 0.0s UT on Greenwich date 10 April 1987?
  //GST = 8h 34m 57.0896s
  //Verified from Astronomical Algorithms 2nd Edition. by. Jean Meeus
  std::string ts2("1987-04-10 19:21:0");
  ptime t2(time_from_string(ts2));

  DecimalHours d3 = GST(t2);

  BOOST_CHECK_CLOSE(d3.get_hours(), 8, 0.5);
  BOOST_TEST(abs(d3.get_minutes() - 34) <= 10);
  BOOST_TEST(d3.get_seconds() >= 0);
  BOOST_TEST(d3.get_seconds() <= 60);

  //What is the local sidereal time on the longitude 82◦ E
  //when the GST is 8h 36m 55.00s OR
  //at 19h 21m 0.00s UT on Greenwich date 10 April 1987
  // Local Sidereal Time at Longitude 82.00° (E) = 14h 05m 42s
  DecimalHours d4 = LST(82, DIRECTION::EAST, d3.get());

  BOOST_CHECK_CLOSE(d4.get_hours(), 14, 0.5);
  BOOST_TEST(abs(d4.get_minutes() - 5) <= 10);
  BOOST_TEST(d4.get_seconds() >= 0);
  BOOST_TEST(d4.get_seconds() <= 60);

  //What was the GST at 06h 02m 0.0s UT on Greenwich date 17 July 2020?
  //GST = 01h 44m 06.667s
  //Verified from http://neoprogrammics.com/sidereal_time_calculator/index.php
  std::string ts3("2020-07-17 6:2:0");
  ptime t3(time_from_string(ts3));

  DecimalHours d5 = GST(t3);

  BOOST_CHECK_CLOSE(d5.get_hours(), 1, 0.5);
  BOOST_TEST(abs(d5.get_minutes() - 44) <= 10);
  BOOST_TEST(d5.get_seconds() >= 0);
  BOOST_TEST(d5.get_seconds() <= 60);

  //What is the local sidereal time on the longitude 37◦ E
  //when the GST is 01h 44m 06.667s OR
  //at at 06h 02m 0.0s UT on Greenwich date 17 July 2020
  //Local Sidereal Time at Longitude 37.00° (E) = 04h 12m 07s
  DecimalHours d6 = LST(37, DIRECTION::EAST, d5.get());

  BOOST_CHECK_CLOSE(d6.get_hours(), 4, 0.5);
  BOOST_TEST(abs(d6.get_minutes() - 12) <= 10);
  BOOST_TEST(d6.get_seconds() >= 0);
  BOOST_TEST(d6.get_seconds() <= 60);
}

BOOST_AUTO_TEST_SUITE_END()


