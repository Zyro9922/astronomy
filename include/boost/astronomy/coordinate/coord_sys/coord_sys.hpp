
/*=============================================================================
  Copyright 2018-2020 Syed Ali Hasan < Zyro9922 - alihasan9922@gmail.com >

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_ASTRONOMY_COORD_SYS_HPP
#define BOOST_ASTRONOMY_COORD_SYS_HPP

#include <cstddef>
#include <type_traits>
#include <boost/static_assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/transform.hpp>

namespace boost { namespace astronomy { namespace coordinate {

namespace bg = boost::geometry;

typedef bg::degree degree;
typedef bg::radian radian;

template
<
    std::size_t DimensionCount,
    typename CoordinateSystem,
    typename CoordinateType=double
>
struct coord_sys
{
protected:
    bg::model::point<CoordinateType, DimensionCount, CoordinateSystem> point;

public:
    typedef CoordinateSystem system;
    typedef CoordinateType type;

    bg::model::point<CoordinateType, DimensionCount, CoordinateSystem> get_point() const
    {
        return this->point;
    }
}; //coord_sys

}}}

#endif //BOOST_ASTRONOMY_COORD_SYS_HPP
