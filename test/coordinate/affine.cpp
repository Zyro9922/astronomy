//
// Created by Ali Hasan on 21/02/20.
//
#define BOOST_TEST_MODULE affine_test

#include <array>
#include <boost/units/io.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/astronomy/coordinate/affine/affine_transformation.hpp>

using namespace boost::astronomy::coordinate;
using namespace boost::units;

typedef long double ld;

BOOST_AUTO_TEST_SUITE(matrix_initialisation_check)
    /**
     * Check for initial identity matrix values
     */
    BOOST_AUTO_TEST_CASE(identity_matrix_check)
    {
        affine_matrix am;

        std::array<std::array<ld,4>, 4> test_identity_matrix = {{ { {1,0,0,0} },
                                                                        { {0,1,0,0} },
                                                                        { {0,0,1,0} },
                                                                        { {0,0,0,1} } }};
        am.display();

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                BOOST_REQUIRE_EQUAL(test_identity_matrix[i][j],am.temp_matrix[i][j]);
    }

    BOOST_AUTO_TEST_CASE(translate_check)
    {
        std::array<std::array<ld,4>, 4> expected_matrix = {{ { {1,0,0,-2} },
                                                                        { {0,1,0,-18} },
                                                                        { {0,0,1,24} },
                                                                        { {0,0,0,1} } }};

        affine_matrix am_translate;
        am_translate.translate(-2,-18,24).display();

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                BOOST_REQUIRE_EQUAL(am_translate.temp_matrix[i][j],expected_matrix[i][j]);
    }

    BOOST_AUTO_TEST_CASE(scale_check)
    {
        std::array<std::array<ld,4>, 4> expected_matrix = {{ { {19,0,0,0} },
                                                                   { {0,21,0,0} },
                                                                   { {0,0,32,0} },
                                                                   { {0,0,0,1} } }};

        affine_matrix am_scale;
        am_scale.scale(19,21,32).display();

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                BOOST_REQUIRE_EQUAL(am_scale.temp_matrix[i][j],expected_matrix[i][j]);
    }

    BOOST_AUTO_TEST_CASE(shear_check)
    {
        std::array<std::array<ld,4>, 4> expected_matrix = {{ { {1,2,3,0} },
                                                                        { {8,1,4,0} },
                                                                        { {5,6,1,0} },
                                                                        { {0,0,0,1} } }};

        affine_matrix am_shear;
        am_shear.shear(2,3,8,4,5,6).display();

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                BOOST_REQUIRE_EQUAL(am_shear.temp_matrix[i][j],expected_matrix[i][j]);
    }

    BOOST_AUTO_TEST_CASE(chaining_check)
    {
        std::array<std::array<ld,4>, 4> expected_matrix = {{ { {19,0,0,-2} },
                                                                   { {0,21,0,-18} },
                                                                   { {0,0,32,24} },
                                                                   { {0,0,0,1} } }};

        affine_matrix am_chain;
        am_chain.translate(-2,-18,24).scale(19,21,32).display();

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                BOOST_REQUIRE_EQUAL(am_chain.temp_matrix[i][j],expected_matrix[i][j]);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(affine_transformation_check)

    BOOST_AUTO_TEST_CASE(transformation)
    {
        typedef cartesian_representation<double,quantity<si::length>,quantity<si::length>,quantity<si::length>> cr;

        //Create a point
        cr p = make_cartesian_representation(10*meter, 23*meter, 17*meter);

        //Create an affine matrix object on which
        // you can apply various transformation
        affine_matrix am_object;
        am_object.translate(-2,-18,24).scale(19,21,32).display();

        //affine_transformation converts the given points
        //into a homogeneous coordinate matrix
        affine_transformation transformation(p);

        //Apply your transformation on the created
        //homogeneous coordinate matrix by passing
        //the object of affine_matrix in transform
        auto ans = transformation.transform(am_object);

        BOOST_CHECK_EQUAL(ans.get_x().value(),190);
        BOOST_CHECK_EQUAL(ans.get_y().value(),483);
        BOOST_CHECK_EQUAL(ans.get_z().value(),544);
    }

BOOST_AUTO_TEST_SUITE_END()
