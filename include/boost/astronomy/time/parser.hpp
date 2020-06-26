/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_PARSER_HPP
#define BOOST_ASTRONOMY_PARSER_HPP

#include <iostream>
#include <string>

using namespace std;

struct DecimalHours {
private:
    double dh = 0;

    double time = 0;
    int hours = 0;
    double minutesRemainder = 0;
    int minutes = 0;
    double secondsRemainder = 0;
    int seconds = 0;

public:
    DecimalHours(double const& d){
      dh = d;

      time = dh;
      hours = (int)time;
      minutesRemainder = (time - hours) * 60;
      minutes = (int)minutesRemainder;
      secondsRemainder = (minutesRemainder - minutes) * 60;
      seconds = (int)secondsRemainder;
    }

    double get() const{
        return (double)dh;
    }

    double get_hours() const{
        return (double)hours;
    }

    double get_minutes() const{
        return (double)minutes;
    }

    double get_seconds() const{
        return (double)seconds;
    }
};

std::ostream& operator << (std::ostream &out, DecimalHours const& dh)
{
    std::string time_string = std::to_string(dh.get_hours()) + "h " + std::to_string(dh.get_minutes()) + "m " + std::to_string(dh.get_seconds()) + "s ";
    return out << "Decimal Hours: " << time_string;
}

#endif //BOOST_ASTRONOMY_PARSER_HPP
