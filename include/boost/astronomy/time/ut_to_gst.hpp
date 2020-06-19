/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_UT_TO_GST_HPP
#define BOOST_ASTRONOMY_UT_TO_GST_HPP

#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/astronomy/time/parser.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

DecimalHours GST(ptime t)
{
    //Get date from UT
    date d = t.date();

    //Get Julian Day Number
    double JD = d.julian_day(); //Ambiguity in Julian precision.

    double S = JD - 2451545.0;

    double T = S/36525.0;

    double T0 = 6.697374558 + (2400.051336 * T) + (0.000025862 * T * T);

    //Reduce the result to the range 0 to 24 by adding or subtracting multiples of 24
    while(T0 < 0 || T0 > 24)
    {
        if(T0 < 0)
        {
            double multiple = ceil(abs(T0)/24.0);
            T0 = T0 + 24.0 * multiple;
        }

        if(T0 > 24)
        {
            double multiple = ceil(abs(T0)/24.0);
            T0 = T0 - 24.0 * multiple;
        }
    }

    //Convert UT to decimal hours
    double UT = ((t.time_of_day().seconds())/60.0 + t.time_of_day().minutes())/60.0 + t.time_of_day().hours();\

    //Multiply UT by 1.002737909
    double A = UT * 1.002737909;

    T0 += A;

    //Add this to T0 and reduce to the range 0 to 24 if necessary by subtracting or adding 24. This is the GST.
    while(T0 < 0 || T0 > 24)
    {
        if(T0 < 0)
        {
            double multiple = ceil(abs(T0)/24.0);
            T0 = T0 + 24.0 * multiple;
        }

        if(T0 > 24)
        {
            double multiple = ceil(abs(T0)/24.0);
            T0 = T0 - 24.0 * multiple;
        }
    }

    //Return GST in decimal hours
    return DecimalHours(T0);
}

#endif //BOOST_ASTRONOMY_UT_TO_GST_HPP
