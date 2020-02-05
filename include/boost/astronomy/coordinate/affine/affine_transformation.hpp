//
// Created by Ali Hasan on 20/01/20.
// Videos Referred
// * Computer Graphics 2013 (https://www.youtube.com/watch?v=4I2S5Xhf24o)
//
// Books Referred
// * Affine Transformations (https://people.cs.clemson.edu/~dhouse/courses/401/notes/affines-matrices.pdf)
//

#ifndef BOOST_ASTRONOMY_AFFINE_TRANSFORMATION_HPP
#define BOOST_ASTRONOMY_AFFINE_TRANSFORMATION_HPP

#include <boost/astronomy/coordinate/coordinate.hpp>
#include <boost/units/systems/si/length.hpp>
#include <array>

#define ROW 4

using namespace boost::astronomy::coordinate;
using namespace boost::units;
using namespace boost::units::si;

typedef long double ld;

typedef cartesian_representation<double,quantity<si::length>,quantity<si::length>,quantity<si::length>> cr;

class affine_matrix
{

public:

    /**
    * Identity Matrix
    *
    * A square matrix in which all the elements of the principal diagonal
    * are ones and all other elements are zeros. The effect of multiplying
    * a given matrix by an identity matrix is to leave the given matrix unchanged.
    */

    std::array<std::array<ld,4>, 4> temp_matrix = {{ { {1,0,0,0} },
                                                     { {0,1,0,0} },
                                                     { {0,0,1,0} },
                                                     { {0,0,0,1} } }};

private:

    std::array<std::array<ld,4>, 4> translate_matrix = {{ { {1,0,0,-1} },
                                                          { {0,1,0,-1} },
                                                          { {0,0,1,-1} },
                                                          { {0,0,0,1} } }};

    std::array<std::array<ld,4>, 4> scale_matrix = {{ { {-1,0,0,0} },
                                                      { {0,-1,0,0} },
                                                      { {0,0,-1,0} },
                                                      { {0,0,0,1} } }};

    std::array<std::array<ld,4>, 4> shear_matrix = {{ { {1,-1,-1,0} },
                                                      { {-1,1,-1,0} },
                                                      { {-1,-1,1,0} },
                                                      { {0,0,0,1} } }};

    //Multiplies temp_matrix with the given matrix
    void multiplyMatrices(const std::array<std::array<ld,4>, 4> &mat)
    {
        ld ans[4][4];

        //Multiply
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                ans[i][j] = 0;
                for (int k = 0; k < 4; k++)
                {
                    ans[i][j] += temp_matrix[i][k] * mat[k][j];
                }
            }
        }

        //Set temp_matrix as ans matrix
        for(int i = 0 ; i < 4 ; i++)
        {
            for(int j = 0 ; j < 4 ; j++)
                temp_matrix[i][j] = ans[i][j];
        }
    }

public:

    void display() {

        printf("\nMatrix:\n");

        for (int i = 0 ; i < 4 ; i++) {

            for (int j = 0; j < 4; ++j) {

                std::cout<< std::setw(4) << temp_matrix[i][j] << " ";

                if (j == 4 - 1)
                    printf("\n");
            }
        }

        printf("\n");
    }

    affine_matrix& translate(ld del_x, ld del_y, ld del_z)
    {
        translate_matrix[0][3] = del_x;
        translate_matrix[1][3] = del_y;
        translate_matrix[2][3] = del_z;

        multiplyMatrices(translate_matrix);

        return *this;
    }

    affine_matrix& scale(ld s_x, ld s_y, ld s_z)
    {
        scale_matrix[0][0] = s_x;
        scale_matrix[1][1] = s_y;
        scale_matrix[2][2] = s_z;

        multiplyMatrices(scale_matrix);

        return *this;
    }

    affine_matrix& shear(ld hxy, ld hxz, ld hyx, ld hyz, ld hzx, ld hzy)
    {
        shear_matrix[0][1] = hxy;
        shear_matrix[0][2] = hxz;
        shear_matrix[1][0] = hyx;
        shear_matrix[1][2] = hyz;
        shear_matrix[2][0] = hzx;
        shear_matrix[2][1] = hzy;

        multiplyMatrices(shear_matrix);

        return *this;
    }
};

/**
 * Multiplies the transformation matrix
 * with the homogeneous coordinate matrix
 */
cr compute_cr(std::array<std::array<ld,4>, 4> firstMatrix, std::array<std::array<ld,1>, 4> secondMatrix, int rowFirst = ROW, int columnFirst = 4, int rowSecond = ROW, int columnSecond = 1)
{
    int i, j, k;
    ld ans[4][1];

    for(i = 0; i < rowFirst; ++i)
    {
        for(j = 0; j < columnSecond; ++j)
        {
            ans[i][j] = 0;
        }
    }

    for(i = 0; i < rowFirst; ++i)
    {
        for(j = 0; j < columnSecond; ++j)
        {
            for(k=0; k<columnFirst; ++k)
            {
                ans[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    ld x = ans[0][0];
    ld y = ans[1][0];
    ld z = ans[2][0];

    return make_cartesian_representation(x*meter, y*meter, z*meter);
}

class affine_transformation{

private:

    cr m_cr;

    /**
     *Here we convert the given cartesian_representation vector
     *into homogeneous coordinate system.
     *
     * One very important point to be noted here is that in the matrix
     * homogeneous_coordinate_matrix[3][0] = 0 instead of conventional 1.
     *
     * As here we are dealing with vectors that are defined by their
     * length and direction. Hence we cannot translate vectors.
     *
     * (https://youtu.be/KAW7lXxMSb4?t=549)
     */
    std::array<std::array<ld,1>, 4> homogeneous_coordinate_matrix = {{ { {-1} },
                                                                       { {-1} },
                                                                       { {-1} },
                                                                       { {0} } }};

    /**
     * From the given cartesian representation we create a
     * homogeneous coordinate matrix
     */
    void make_hcm(const cr& a)
    {
        homogeneous_coordinate_matrix[0][0] = a.get_x().value();
        homogeneous_coordinate_matrix[1][0] = a.get_y().value();
        homogeneous_coordinate_matrix[2][0] = a.get_z().value();
    }

public:
    explicit affine_transformation(const cr& a) { m_cr = a; };

    cr transform(affine_matrix a)
    {
        make_hcm(m_cr);
        return compute_cr(a.temp_matrix,homogeneous_coordinate_matrix);
    }

};

#endif //BOOST_ASTRONOMY_AFFINE_TRANSFORMATION_HPP
