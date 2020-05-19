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

            //Angle Base Class
            template
                    <
                    typename CoordinateType = double,
                    typename AngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct Angle {
                virtual AngleQuantity get() {}
            };

            //Right Ascension
            template
                    <
                            typename CoordinateType = double,
                            typename RightAscensionQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct RightAscension : public virtual Angle<CoordinateType,RightAscensionQuantity> {
            private:
                RightAscensionQuantity ra;
            public:
                RightAscension() {}

                RightAscension(RightAscensionQuantity const& _ra) : ra(_ra) {}

                RightAscensionQuantity get() override{
                    return ra;
                }

                void print() {
                    std::cout << "Right Ascension: " << ra.value() << std::endl;
                }

                //TODO: Use SOFA to convert
//                double convert_to_ha()
//                {
//
//                }
            };

            //Hour Angle
            template<
                    typename CoordinateType = double,
                    typename HourAngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>
                    >
            struct HourAngle : public virtual Angle<CoordinateType,HourAngleQuantity> {
            private:
                HourAngleQuantity ha;
            public:
                HourAngle() {}

                HourAngle(HourAngleQuantity _ha) : ha(_ha) {}

                HourAngleQuantity get() override{
                    return ha;
                }

                void print() {
                    std::cout << "Hour Angle: " << ha.value() << std::endl;
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
                            typename AngleQuantity = bu::quantity<bu::si::plane_angle, CoordinateType>,
                            typename XQuantity = Angle<CoordinateType,AngleQuantity>,
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
                    return RightAscension<double,AngleQuantity>((bg::get<0>(this->point)));
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
                                    X.get()
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

//            template
//                    <
//                    typename CoordinateType,
//                    template<typename Unit1, typename CoordinateType_> class AngleQuantity,
//                    template<typename CoordinateType_, AngleQuantity<typename Unit2, typename CoordinateType_>> class XQuantity,
//                    template<typename Unit3, typename CoordinateType_> DeclinationQuantity ,
//                    typename Unit1,
//                    typename Unit2,
//                    typename Unit3
//                    >
//            equatorial_coord
//                    <
//                            CoordinateType,
//                            AngleQuantity<Unit1,CoordinateType>
//                            XQuantity<CoordinateType,AngleQuantity<Unit2,CoordinateType>>,
//                            DeclinationQuantity<Unit3, CoordinateType>
//                    > make_equatorial_coord
//                    (
//                            XQuantity<CoordinateType,AngleQuantity<Unit2,CoordinateType>> const &X,
//                            DeclinationQuantity<Unit3, CoordinateType> const &Declination
//                    ) {
//                return equatorial_coord
//                        <
//                                CoordinateType,
//                                AngleQuantity<Unit2,CoordinateType>,
//                                XQuantity<CoordinateType,AngleQuantity<Unit2,CoordinateType>>,
//                                DeclinationQuantity<Unit3, CoordinateType>
//                        >(X, Declination);
//            }

            //Print Equatorial Coordinates
            template
                    <
                            typename CoordinateType,
                            class AngleQuantity,
                            class XQuantity,
                            class DeclinationQuantity
                    >
            std::ostream &operator<<(std::ostream &out, equatorial_coord
                    <CoordinateType,AngleQuantity, XQuantity, DeclinationQuantity> const &point) {
                out << "Equatorial Coordinate (X: "
                    << point.get_X() << " , Declination: "
                    << point.get_Declination() << ")";

                return out;
            }
        }
    }
}
#endif //BOOST_ASTRONOMY_EQUATORIAL_COORD_HPP
