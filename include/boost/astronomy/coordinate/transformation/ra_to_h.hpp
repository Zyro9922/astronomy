//
// Created by Ali Hasan on 16/01/20.
//

#ifndef BOOST_ASTRONOMY_RA_TO_H_HPP
#define BOOST_ASTRONOMY_RA_TO_H_HPP

#include <math.h>
#include <tuple>
#include <cmath>
#include <boost/astronomy/coordinate/coordinate.hpp>
#include <boost/astronomy/coordinate/transformation/equatorial_to_horizontal.hpp>
#include <boost/astronomy/coordinate/sky_point.hpp>
#include <boost/astronomy/coordinate/frame.hpp>
#include <boost/astronomy/coordinate/arithmetic.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/velocity.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/io.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/geometry.hpp>

namespace bud = boost::units::degree;
using namespace boost::geometry;

typedef long double ld;

class day_month_year
{
public:
    ld day, month, year;

    day_month_year(ld d, ld m, ld y)
    {
        day = d;
        month = m;
        year = y;
    }
};


/**
 * Page 9
 *
 * To calculate the Julian date corresponding to the Greenwich calendar date
 */
ld get_Julian_Day_Number(ld d, ld m, ld y)
{
    ld _m,_y;
    if(m == 1 || m == 2)
    {
        _m = m + 12;
        _y = y - 1;
    } else {
        _m = m;
        _y = y;
    }

    ld A = 0,B = 0,C = 0,D = 0;

    if(y >= 1582)
    {
        A = trunc(_y/100);
        B = 2 - A + trunc(A/4);
    }
    else
        B = 0;

    if(_y < 0)
        C = trunc((365.25*_y)-0.75);
    else
        C = trunc(365.25*_y);

    D = trunc(30.6001 * (_m + 1));

    ld JD = B + C + D + d + 1720994.5;
    return JD;
}

/**
 * Page 11
 * To convert a given Julian date into its counterpart in the Gregorian calendar
 */
day_month_year Julian_Date_to_GreenWhich(ld JD)
{
    JD = JD + 0.5;

    ld F = JD - (int)JD;
    ld I = JD - F;

    ld B,C,D,E,G;
    if(I > 2299160)
    {
        ld A = trunc( (I - 1867216.25) / 36524.25);
        B = I + A - trunc(A/4) + 1;
    } else  B = I;

    C = B + 1524;
    D = trunc( (C - 122.1)/365.25 );
    E = trunc(365.25 * D);
    G = trunc( (C - E) / 30.6001 );

    ld day = C - E + F - trunc(30.6001 * G);

    ld m;

    if( G < 13.5 )
        m = G - 1;
    else
        m = G - 13;

    ld y;

    if( m > 2.5 )
        y = D - 4716;
    else
        y = D - 4715;

    return day_month_year(day,m,y);
}

/**
 * Simply converts given hours,min,sec to decimal hours
 */
ld to_decimal_hours(ld hours, ld min, ld sec)
{
    return hours + (min + (sec/60))/60;
}

/**
 * Zone Time is calculated by removing Day Light Saving Time
 */
ld to_zone_time(ld hours, ld min, ld sec, ld DST)
{
    hours = hours - DST;
    return to_decimal_hours(hours, min, sec);
}

/**
 * To calculate UT
 */
ld get_UT(ld hours, ld time_zone)
{
    return hours - time_zone;
}

/**
 * To get greenwhich calendar day corresponding to the calculated UT
 */
ld get_greenwhich_calendar_day(ld local_calendar_day, ld UT)
{
    return local_calendar_day + (UT/24.0);
}

/**
 * Convert the Julian calendar date back into the Greenwich calendar date
 */
day_month_year GD_day_month_year(ld greenwhich_calendar_day,ld LCTday, ld LCTmonth, ld LCTyear)
{
    ld JD = get_Julian_Day_Number(greenwhich_calendar_day,LCTmonth,LCTyear);

    return Julian_Date_to_GreenWhich(JD);
}

ld get_GST(ld UT, ld GW_day,ld GW_month,ld GW_year)
{
    GW_day = trunc(GW_day);

    ld JD = get_Julian_Day_Number(GW_day,GW_month,GW_year);
    ld S = JD - 2451545.0;
    ld T = S/36525.0;
    ld _T = 6.697374558 + (2400.051336*T) + (0.000025862*pow(T,2));
    if(_T > 24)
        while(_T > 24)  _T = _T - 24;
    else if(_T < 0)
        while(_T < 0)   _T = _T + 24;

    UT = UT * 1.002737909;

    ld GST = _T + UT;
    if(GST > 24)
        while(GST > 24)  GST = GST - 24;
    else if(GST < 0)
        while(GST < 0)   GST = GST + 24;

    return GST;
}

ld get_LST(ld longitude, ld GST)
{
    ld long_hour = longitude/15;

    long_hour += GST;

    if(long_hour > 24)
        while(long_hour > 24)  long_hour = long_hour - 24;
    else if(long_hour < 0)
        while(long_hour < 0)   long_hour = long_hour + 24;
    return long_hour;
}

ld ra_to_h(ld ra, ld longitude,ld LCT_hour,ld LCT_min,ld LCT_sec, ld DST,ld time_zone,
                                ld local_calendar_day, ld local_calendar_month, ld local_calendar_year)
{
    ld zone_time = to_zone_time(LCT_hour,LCT_min,LCT_sec,DST);

    ld temp_UT = get_UT(zone_time,time_zone);

    ld GCD = get_greenwhich_calendar_day(local_calendar_day,temp_UT);

    day_month_year dmy1 = GD_day_month_year(GCD,local_calendar_day,local_calendar_month,local_calendar_year);

    ld GST = get_GST(temp_UT,trunc(dmy1.day),dmy1.month,dmy1.year);

    ld LST = get_LST(longitude,GST);

    ld Hour_Angle = LST - ra;

    if(Hour_Angle < 0)
        Hour_Angle = Hour_Angle + 24;

    return Hour_Angle;
}

#endif //BOOST_ASTRONOMY_RA_TO_H_HPP
