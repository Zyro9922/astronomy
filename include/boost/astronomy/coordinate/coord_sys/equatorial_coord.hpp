#ifndef BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
#define BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP

#include <iostream>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/astronomy/coordinate/coord_sys/coord_sys.hpp>

namespace boost {
    namespace astronomy {
        namespace coordinate {

            namespace bu = boost::units;
            namespace bg = boost::geometry;
            namespace bud = boost::units::degree;

            struct Angle {

                void get() {

                }

            };

            // TODO: Create template to accept degree or radian
            struct RightAscension : public virtual Angle {

            private:
                double ra;
            public:
                RightAscension() : ra(0.0) {}

                RightAscension(double _ra) : ra(_ra) {}

                void set(double _ra) {
                    ra = _ra;
                }

                double get() {
                    return ra;
                }

                //TODO: Use SOFA to convert
//                double convert_to_ha()
//                {
//
//                }
            };

            // TODO: Create template to accept degree or radian
            struct HourAngle : public virtual Angle {

            private:
                double ha;
            public:
                HourAngle() : ha(0.0) {}

                HourAngle(double _ha) : ha(_ha) {}

                void set(double _ha) {
                    ha = _ha;
                }

                double get() {
                    return ha;
                }

//                //TODO: Use SOFA to convert
//                double convert_to_ra()
//                {
//
//                }
            };

            //Equatorial Coordinate Struct
            template
                    <
                            typename CoordinateType = double,
                            typename XQuantity = Angle,
                            typename DeclinationQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct equatorial_coord : public coord_sys
                    <2, bg::cs::spherical<bg::degree>, CoordinateType> {
            public:
                typedef XQuantity quantity1;
                typedef DeclinationQuantity quantity2;

                //Default constructor
                equatorial_coord() {}

                equatorial_coord
                        (
                                XQuantity const &X,
                                DeclinationQuantity const &Declination
                        ) {
                    this->set_X_Declination(X, Declination);
                }

                std::tuple<XQuantity, DeclinationQuantity> get_X_Declination() const {
                    return std::make_tuple(this->get_X(), this->get_Declination());
                }

                XQuantity get_X() const {
                    return RightAscension((bg::get<0>(this->point)));
                }

                DeclinationQuantity get_Declination() const {
                    return static_cast<DeclinationQuantity>
                    (
                            bu::quantity<bu::si::plane_angle, CoordinateType>::from_value
                                    (bg::get<1>(this->point))
                    );
                }

                //Set value of X and Declination
                void set_X_Declination
                        (
                                XQuantity const &X,
                                DeclinationQuantity const &Declination
                        ) {
                    this->set_X(X);
                    this->set_Declination(Declination);
                }

                //Set X
                void set_X(XQuantity const &X) {
                    bg::set<0>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(23.0 *bud::degree).value()
                            );
                }

                //Set Declination
                void set_Declination(DeclinationQuantity const &Declination) {
                    bg::set<1>
                            (
                                    this->point,
                                    static_cast<bu::quantity<bu::si::plane_angle, CoordinateType>>(Declination).value()
                            );
                }

            }; //equatorial_coord

            template
                    <
                            typename CoordinateType,
                            typename XQuantity,
                            template<typename Unit2, typename CoordinateType_> class DeclinationQuantity,
                            typename Unit2
                    >
            equatorial_coord
                    <
                            CoordinateType,
                            XQuantity,
                            DeclinationQuantity<Unit2, CoordinateType>
                    > make_equatorial_coord
                    (
                            XQuantity const &X,
                            DeclinationQuantity<Unit2, CoordinateType> const &Declination
                    ) {
                return equatorial_coord
                        <
                                CoordinateType,
                                XQuantity,
                                DeclinationQuantity<Unit2, CoordinateType>
                        >(X, Declination);
            }

            //Print Equatorial Coordinates
            template
                    <
                            typename CoordinateType,
                            class XQuantity,
                            class DeclinationQuantity
                    >
            std::ostream &operator<<(std::ostream &out, equatorial_coord
                    <CoordinateType, XQuantity, DeclinationQuantity> const &point) {
                out << "Equatorial Coordinate (X: "
                    << (point.get_X()).get() << " , Declination: "
                    << point.get_Declination() << ")";

                return out;
            }

        }
    }
}
#endif //BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
