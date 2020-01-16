//
// Created by Ali Hasan on 16/01/20.
//
#ifndef BOOST_ASTRONOMY_EQUATORIAL_TO_HORIZONTAL_HPP
#define BOOST_ASTRONOMY_EQUATORIAL_TO_HORIZONTAL_HPP
#include <iostream>
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
#include <boost/astronomy/coordinate/transformation/ra_to_h.hpp>
#include <utility>
#include <cmath>
#include <math.h>
using namespace std;

#define PI 3.14159265

namespace bud = boost::units::degree;
typedef long double ld;

ld ra_to_h(ld ra, ld longitude,ld LCT_hour,ld LCT_min,ld LCT_sec, ld DST,ld time_zone,
           ld local_calendar_day, ld local_calendar_month, ld local_calendar_year);

//8.5.
//If negative, the true azimuth is A = A′(positive).
//If positive, the true azimuth is A = 360 − A′
//This function is written outside namespace boost { namespace astronomy { namespace coordinate
//to avoid collision with relation.hpp file
ld azimuth(ld sinH_value, ld temp_azimuth)
{
    if(sinH_value < 0)
        return abs(temp_azimuth);
    else
        return (360 - temp_azimuth);
}

namespace boost { namespace astronomy { namespace coordinate {

            using namespace boost::astronomy::coordinate;
            using namespace boost::units;
            using namespace boost::units::si;
            using namespace boost::posix_time;
            using namespace boost::geometry;

            typedef alt_az<
                    spherical_representation<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>,quantity<si::length>>,
            spherical_coslat_differential<>> horizon;

            typedef base_equatorial_frame<
                    spherical_representation<double, quantity<bud::plane_angle>, quantity<bud::plane_angle>,quantity<si::length>>,
                    spherical_coslat_differential<>> equatorial;

            horizon make_Horizon(double alt,double az, double dist)
            {
                return horizon(alt * bud::degree, az * bud::degree, dist * meters);
            }

            //1. Convert hour angle to decimal hours
            ld hour_angle_to_decimal_hours(ld h, ld m, ld s)
            {
                /**
                  Assumption 24hour format
                  1. Take the number of seconds and divide by 60.
                  2. Add this to the number of minutes and divide by 60.
                  3. Add the number of hours.
                 */
                return h + (m+(s/60))/60;
            }

//2. Multiply by 15 to convert H to degrees
            ld H_to_degree(ld H)
            {
                return H*15;
            }

//3. Convert δ into decimal degrees
            ld declination_angle_to_decimal_degree(ld degree, ld minutes, ld seconds)
            {
                return degree + (minutes + (seconds/60)) / 60;
            }

//4. Find sina = sinδ sinφ +cosδ cosφ cosH
            ld sina(ld declination, ld latitude, ld H)
            {
                //sina = sinδ sinφ +cosδ cosφ cosH

                //Radian to degree conversion
                declination = declination*PI/180;
                latitude = latitude*PI/180;
                H = H*PI/180;
                return sin(declination) * sin(latitude) + cos(declination) * cos(latitude) * cos(H);
            }

//5. Take inverse sin to find a
            ld altitude(ld sina_val)
            {
                return asin(sina_val) * 180.0 / PI;
            }

//6. Find cosA = sinδ−sinφ sina / cosφcosa
            ld cosA(ld declination, ld latitude, ld H, ld altitude)
            {
                //Radian to degree conversion
                declination = declination*PI/180;
                latitude = latitude*PI/180;
                H = H*PI/180;
                altitude = altitude*PI/180;
                return ( sin(declination) - sin(latitude) * sin(altitude) ) / ( cos(latitude) * cos(altitude) );
            }

//7. Take inverse cos to find A'
            ld temp_azimuth(ld cosa_value)
            {
                return acos(cosa_value) * 180.0 / PI;
            }

//8. Find sinH
            ld sinH(ld H)
            {
                H = H*PI/180;
                return sin(H);
            }

            struct DMS
            {
                DMS(double value)
                {
                    degrees = std::floor(value);
                    double rem = (value-degrees) * 60;
                    minutes = std::floor(rem);
                    seconds = (rem-minutes) * 60;
                    std::cout<<degrees<<"◦ "<<minutes<<"' "<<seconds<<"''"<<std::endl;
                }

                operator double() const
                {
                    return degrees + minutes/60 + seconds/3600;
                }

                double degrees;
                double minutes;
                double seconds;
            };

//9. Convert a and A to degrees, minutes and seconds.
            void printHorizonCoordinates(ld azimuth, ld altitude)
            {
                //A - azimuth
                //A'- Temp azimuth
                //a - altitude
                std::cout<<"Azimuth: ";
                DMS printAzimuth(azimuth);
                std::cout<<"\nAltitude: ";
                DMS printAltitude(altitude);
            }

            horizon equatorial_to_horizon_hourAngle(ld hourAngle_in_degrees,
                                       equatorial e,
                                       ld latitude)
            {

                ld declination_in_degree = e.get_dec().value();

                ld altitude_val = altitude( sina ( declination_in_degree,
                                                   latitude,
                                                   hourAngle_in_degrees) );

                ld azimuth_val = azimuth( sinH(hourAngle_in_degrees),
                                          temp_azimuth( cosA(declination_in_degree, latitude, hourAngle_in_degrees, altitude_val) ));

                ld dist = 0;

                printHorizonCoordinates(azimuth_val,altitude_val);

                return make_Horizon(altitude_val,azimuth_val,dist);
            }

            horizon equatorial_to_horizon(equatorial e,
                                          ld LCT_hour,ld LCT_min,ld LCT_sec,
                                          ld DST,
                                          ld time_zone,
                                          ld local_calendar_day, ld local_calendar_month, ld local_calendar_year,
                                          ld longitude,
                                          ld latitude)
            {
                ld hourAngle = ra_to_h(e.get_ra().value(), longitude,
                LCT_hour, LCT_min,LCT_sec,
                DST,
                time_zone,
                local_calendar_day, local_calendar_month, local_calendar_year);

                hourAngle *= 15;

                return equatorial_to_horizon_hourAngle(hourAngle,e,latitude);
            }
}}}
#endif //BOOST_ASTRONOMY_EQUATORIAL_TO_HORIZONTAL_HPP
