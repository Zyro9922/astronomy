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
    double dh;

    double time = dh;
    int hours = (int)time;
    double minutesRemainder = (time - hours) * 60;
    int minutes = (int)minutesRemainder;
    double secondsRemainder = (minutesRemainder - minutes) * 60;
    int seconds = (int)secondsRemainder;

public:
    DecimalHours(double const& d) : dh(d) {}

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
