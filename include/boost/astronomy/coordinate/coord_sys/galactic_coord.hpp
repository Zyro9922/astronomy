#ifndef BOOST_ASTRONOMY_GALACTIC_COORD_HPP
#define BOOST_ASTRONOMY_GALACTIC_COORD_HPP

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/physical_dimensions/plane_angle.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/systems/si/dimensionless.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

/**
 * Galactic Longitude (l) varies from 0◦ to 360◦ in the same direction as increasing right ascension.
 * Galactic Latitude (b) varies 0◦ to 90◦ north of the plane of Galaxy and from 0◦ to −90◦ south of it.
**/

namespace boost {
    namespace astronomy {
        namespace coordinate {

            namespace bu = boost::units;
            namespace bg = boost::geometry;

            template
                    <
                            typename CoordinateType = double,
                            typename GalacticLongitudeQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
                            typename GalacticLatitudeQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct galactic_coord : public coord_sys
                    <2, bg::cs::spherical<bg::degree>, CoordinateType> {
            public:
                typedef GalacticLongitudeQuantity quantity1;
                typedef GalacticLatitudeQuantity quantity2;

                //Default constructor
                galactic_coord() {}

                galactic_coord
                        (
                                GalacticLongitudeQuantity const &GLon,
                                GalacticLatitudeQuantity const &GLat
                        )
                {
                    this->set_GLon_GLat(GLon, GLat);
                }

                std::tuple<GalacticLongitudeQuantity, GalacticLatitudeQuantity> get_GLon_GLat() const {
                    return std::make_tuple(this->get_GLon(), this->get_GLat());
                }

                GalacticLongitudeQuantity get_GLon() const {
                    return static_cast<GalacticLongitudeQuantity>
                    (
                            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                                    (bg::get<0>(this->point))
                    );
                }

                GalacticLatitudeQuantity get_GLat() const {
                    return static_cast<GalacticLatitudeQuantity>
                    (
                            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                                    (bg::get<1>(this->point))
                    );
                }

                //Set value of GLon and GLat
                void set_GLon_GLat
                        (
                                GalacticLongitudeQuantity const &GLon,
                                GalacticLatitudeQuantity const &GLat
                        ) {
                    this->set_GLon(GLon);
                    this->set_GLat(GLat);
                }

                //Set GLon
                void set_GLon(GalacticLongitudeQuantity const &GLon) {
                    bg::set<0>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(GLon).value()
                            );
                }

                //Set GLat
                void set_GLat(GalacticLatitudeQuantity const &GLat) {
                    bg::set<1>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(GLat).value()
                            );
                }

            }; //galactic_coord

            template
                    <
                            typename CoordinateType,
                            template<typename Unit1, typename CoordinateType_> class GalacticLongitudeQuantity,
                            template<typename Unit2, typename CoordinateType_> class GalacticLatitudeQuantity,
                            typename Unit1,
                            typename Unit2
                    >
            galactic_coord
                    <
                            CoordinateType,
                            GalacticLongitudeQuantity<Unit1, CoordinateType>,
                            GalacticLatitudeQuantity<Unit2, CoordinateType>
                    > make_galactic_coord
                    (
                            GalacticLongitudeQuantity<Unit1, CoordinateType> const &GLon,
                            GalacticLatitudeQuantity<Unit2, CoordinateType> const &GLat
                    ) {
                return galactic_coord
                        <
                                CoordinateType,
                                GalacticLongitudeQuantity<Unit1, CoordinateType>,
                                GalacticLatitudeQuantity<Unit2, CoordinateType>
                        >(GLon, GLat);
            }

            //Print Galactic Coordinates
            template
                    <
                            typename CoordinateType,
                            class GalacticLongitudeQuantity,
                            class GalacticLatitudeQuantity
                    >
            std::ostream& operator<< (std::ostream &out, galactic_coord
                    <CoordinateType, GalacticLongitudeQuantity, GalacticLatitudeQuantity> const& point)
            {
                out << "Galactic Coordinate (Galactic Longitude: "
                    << point.get_GLon() << " , Galactic Latitude: "
                    << point.get_GLat() << ")";

                return out;
            }

        }
    }
}

#endif //BOOST_ASTRONOMY_GALACTIC_COORD_HPP
