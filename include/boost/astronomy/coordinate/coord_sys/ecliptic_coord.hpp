#ifndef BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP
#define BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/physical_dimensions/plane_angle.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

/**
 * Uses vernal equinox, à, as its reference direction
 */

namespace boost {
    namespace astronomy {
        namespace coordinate {

            namespace bu = boost::units;
            namespace bg = boost::geometry;

            template
                    <
                            typename CoordinateType = double,
                            typename EclipticLonQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
                            typename EclipticLatQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct ecliptic_coord : public coord_sys
                    <2, bg::cs::spherical<bg::degree>, CoordinateType> {
            public:
                typedef EclipticLonQuantity quantity1;
                typedef EclipticLatQuantity quantity2;

                //Default constructor
                ecliptic_coord() {}

                ecliptic_coord
                        (
                                EclipticLonQuantity const &EclipticLon,
                                EclipticLatQuantity const &EclipticLat
                        ) {
                    this->set_EclipticLon_EclipticLat(EclipticLon, EclipticLat);
                }

                //Create a tuple of Ecliptic Longitude and Ecliptic Latitude
                std::tuple<EclipticLonQuantity, EclipticLatQuantity> get_EclipticLon_EclipticLat() const {
                    return std::make_tuple(this->get_EclipticLon(), this->get_EclipticLat());
                }

                //Get Ecliptic Longitude
                EclipticLonQuantity get_EclipticLon() const {
                    return static_cast<EclipticLonQuantity>
                    (
                            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                                    (bg::get<0>(this->point))
                    );
                }

                //Get Ecliptic Latitude
                EclipticLatQuantity get_EclipticLat() const {
                    return static_cast<EclipticLatQuantity>
                    (
                            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                                    (bg::get<1>(this->point))
                    );
                }

                //Set value of Ecliptic Longitude and Ecliptic Latitude
                void set_EclipticLon_EclipticLat
                        (
                                EclipticLonQuantity const &EclipticLon,
                                EclipticLatQuantity const &EclipticLat
                        ) {
                    this->set_EclipticLon(EclipticLon);
                    this->set_EclipticLat(EclipticLat);
                }

                //Set Ecliptic Longitude
                void set_EclipticLon(EclipticLonQuantity const &EclipticLon) {
                    bg::set<0>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(EclipticLon).value()
                            );
                }

                //Set Ecliptic Latitude
                void set_EclipticLat(EclipticLatQuantity const &EclipticLat) {
                    bg::set<1>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(EclipticLat).value()
                            );
                }

            }; //ecliptic_coord

            //Make Ecliptic Coordinate
            template
                    <
                            typename CoordinateType,
                            template<typename Unit1, typename CoordinateType_> class EclipticLonQuantity,
                            template<typename Unit2, typename CoordinateType_> class EclipticLatQuantity,
                            typename Unit1,
                            typename Unit2
                    >
            ecliptic_coord
                    <
                            CoordinateType,
                            EclipticLonQuantity<Unit1, CoordinateType>,
                            EclipticLatQuantity<Unit2, CoordinateType>
                    > make_ecliptic_coord
                    (
                            EclipticLonQuantity<Unit1, CoordinateType> const &EclipticLon,
                            EclipticLatQuantity<Unit2, CoordinateType> const &EclipticLat
                    ) {
                return ecliptic_coord
                        <
                                CoordinateType,
                                EclipticLonQuantity<Unit1, CoordinateType>,
                                EclipticLatQuantity<Unit2, CoordinateType>
                        >(EclipticLon, EclipticLat);
            }

            //Print Ecliptic Coordinates
            template
                    <
                            typename CoordinateType,
                            class EclipticLonQuantity,
                            class EclipticLatQuantity
                    >
            std::ostream &operator<<(std::ostream &out, ecliptic_coord
                    <CoordinateType, EclipticLonQuantity, EclipticLatQuantity> const &point) {
                out << "Ecliptic Coordinate (Ecliptic Longitude: "
                    << point.get_EclipticLon() << " , Ecliptic Latitude: "
                    << point.get_EclipticLat() << ")";

                return out;
            }
        }
    }
}

#endif //BOOST_ASTRONOMY_ECLIPTIC_COORD_HPP