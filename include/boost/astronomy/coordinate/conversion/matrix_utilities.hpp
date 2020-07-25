/*=============================================================================
Copyright 2020 Syed Ali Hasan <alihasan9922@gmail.com>

Distributed under the Boost Software License, Version 1.0. (See accompanying
file License.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_MATRIX_UTILITIES_HPP
#define BOOST_ASTRONOMY_MATRIX_UTILITIES_HPP

#include <iostream>
#include <cmath>

#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

using namespace std;
using namespace boost::numeric::ublas;
namespace  bnu = boost::numeric::ublas;

namespace boost { namespace astronomy { namespace coordinate {

/**
 * radians = degrees * (Math.PI/180);
 * degrees = radians * (180/Math.PI);
 */

//Phi φ is the geographical latitude
//ST is the local sidereal time
//ε is the obliquity of the ecliptic.

template
<typename ElementType = double>
struct col_vec
{
 private:
  double _u = 0.0 * M_PI/180;
  double _v = 0.0 * M_PI/180;
 public:

  matrix<ElementType> vec = matrix<ElementType>(3, 1);

  col_vec() {}

  col_vec(ElementType u, ElementType v)
  {
    _u = u * M_PI/180;
    _v = v * M_PI/180;

    vec(0,0) = std::cos(_u) * std::cos(_v);
    vec(1,0) = std::sin(_u) * std::cos(_v);
    vec(2,0) = std::sin(_v);
  }

  matrix<ElementType> get()
  {
    return vec;
  }

  std::string to_string()
  {
    return "Column Vector";
  }
};

template
<typename ElementType = double>
struct ha_dec_hor
{
 private:
  double _phi = 0 * M_PI/180;

 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  ha_dec_hor() {}

  ha_dec_hor(ElementType phi)
  {
    _phi = phi * M_PI/180;

    conv(0,0) = -std::sin(_phi);
    conv(0,1) = 0;
    conv(0,2) = std::cos(_phi);
    conv(1,0) = 0;
    conv(1,1) = -1;
    conv(1,2) = 0;
    conv(2,0) = std::cos(_phi);
    conv(2,1) = 0;
    conv(2,2) = std::sin(_phi);
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Equatorial Coordinate Hour Angle to and from Horizon";
  }

};

template
<typename ElementType = double>
struct ha_dec_ra_dec
{
 private:
  double _ST = 0 * M_PI/180;

 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  ha_dec_ra_dec() {}

  ha_dec_ra_dec(ElementType ST)
  {
    _ST = ST * M_PI/180;

    conv(0,0) = std::cos(_ST);
    conv(0,1) = std::sin(_ST);
    conv(0,2) = 0;
    conv(1,0) = std::sin(_ST);
    conv(1,1) = -std::cos(_ST);
    conv(1,2) = 0;
    conv(2,0) = 0;
    conv(2,1) = 0;
    conv(2,2) = 1;
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Equatorial Coordinate Hour Angle to and from Equatorial Coordinate Right Ascension";
  }
};

template
    <typename ElementType = double>
struct ecliptic_to_ra_dec
{
 private:
  double _obliquity = 0 * M_PI/180;

 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  ecliptic_to_ra_dec() {}

  ecliptic_to_ra_dec(ElementType obliquity)
  {
    _obliquity = obliquity * M_PI/180;

    conv(0,0) = 1;
    conv(0,1) = 0;
    conv(0,2) = 0;
    conv(1,0) = 0;
    conv(1,1) = std::cos(_obliquity);
    conv(1,2) = -std::sin(_obliquity);
    conv(2,0) = 0;
    conv(2,1) = std::sin(_obliquity);
    conv(2,2) = std::cos(_obliquity);
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Ecliptic to Equatorial Coordinate Right Ascension";
  }

};

template
    <typename ElementType = double>
struct ra_dec_to_ecliptic
{
 private:
  double _obliquity = 0 * M_PI/180;

 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  ra_dec_to_ecliptic() {}

  ra_dec_to_ecliptic(ElementType obliquity)
  {
    _obliquity = obliquity * M_PI/180;

    conv(0,0) = 1;
    conv(0,1) = 0;
    conv(0,2) = 0;
    conv(1,0) = 0;
    conv(1,1) = std::cos(_obliquity);
    conv(1,2) = -std::sin(_obliquity);
    conv(2,0) = 0;
    conv(2,1) = std::sin(_obliquity);
    conv(2,2) = std::cos(_obliquity);
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Equatorial Coordinate Right Ascension to Ecliptic";
  }

};

template
    <typename ElementType = double>
struct galactic_to_ra_dec
{
 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  galactic_to_ra_dec()
  {
    conv(0,0) = -0.0669887;
    conv(0,1) = -0.8727558;
    conv(0,2) = -0.4835389;
    conv(1,0) = 0.4927285;
    conv(1,1) = -0.4503470;
    conv(1,2) = 0.7445846;
    conv(2,0) = -0.8676008;
    conv(2,1) = -0.1883746;
    conv(2,2) = 0.4601998;
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Galactic to Equatorial Coordinate Right Ascension";
  }

};

template
<typename ElementType = double>
struct ra_dec_to_galactic
{
 public:
  matrix<ElementType> conv = matrix<ElementType>(3, 3);

  ra_dec_to_galactic()
  {
    conv(0,0) = -0.0669887;
    conv(0,1) = 0.8727558;
    conv(0,2) = -0.4835389;
    conv(1,0) = -0.4927285;
    conv(1,1) = -0.4503470;
    conv(1,2) = -0.7445846;
    conv(2,0) = -0.8676008;
    conv(2,1) = 0.1883746;
    conv(2,2) = 0.4601998;
  }

  matrix<ElementType> get()
  {
    return conv;
  }

  std::string to_string()
  {
    return "Equatorial Coordinate Right Ascension to Galactic";
  }

};

//template
//<typename ElementType = double>
struct extract_coordinates{
 private:
  double theta = 0;
  double phi = 0;

 public:
  extract_coordinates(){}

  extract_coordinates(matrix<double> col_vec)
  {
    double m = col_vec(0,0);
    double n = col_vec(1,0);
    double p = col_vec(2,0);

    theta = atan2(n,m) * (180/M_PI);
    phi = asin(p) * (180/M_PI);
  }

  void get_coordinates()
  {
    std::cout << "Theta: " << theta << " Phi: " << phi << endl;
  }
};
}}}

#endif  // BOOST_ASTRONOMY_MATRIX_UTILITIES_HPP
