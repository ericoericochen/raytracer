#include "../include/transforms.h"
#include "../include/matrix.h"

namespace transforms
{
    Matrix eye()
    {
        Matrix eye = Matrix(4);

        // set diagonals to 1
        for (int i = 0; i < 4; i++)
        {
            eye.set(i, i, 1);
        }

        return eye;
    }

    Matrix translation(double x, double y, double z)
    {
        auto matrix = eye();

        // set last column to x, y, z, 1
        matrix.set(0, 3, x);
        matrix.set(1, 3, y);
        matrix.set(2, 3, z);

        return matrix;
    }

    Matrix scaling(double x, double y, double z)
    {
        auto matrix = eye();

        // set diagonal to x, y, z, 1
        matrix.set(0, 0, x);
        matrix.set(1, 1, y);
        matrix.set(2, 2, z);

        return matrix;
    }

    Matrix rotation_x(double radians)
    {
        auto matrix = eye();

        matrix.set(1, 1, cos(radians));
        matrix.set(2, 1, sin(radians));
        matrix.set(1, 2, -sin(radians));
        matrix.set(2, 2, cos(radians));

        return matrix;
    }

    Matrix rotation_y(double radians)
    {
        auto matrix = eye();

        matrix.set(0, 0, cos(radians));
        matrix.set(2, 0, -sin(radians));
        matrix.set(0, 2, sin(radians));
        matrix.set(2, 2, cos(radians));

        return matrix;
    }

    Matrix rotation_z(double radians)
    {

        auto matrix = eye();

        matrix.set(0, 0, cos(radians));
        matrix.set(1, 0, sin(radians));
        matrix.set(0, 1, -sin(radians));
        matrix.set(1, 1, cos(radians));

        return matrix;
    }

    Matrix shearing(double xy = 0, double xz = 0, double yx = 0, double yz = 0, double zx = 0, double zy = 0)
    {
        auto matrix = eye();

        matrix.set(0, 1, xy);
        matrix.set(0, 2, xz);
        matrix.set(1, 0, yx);
        matrix.set(1, 2, yz);
        matrix.set(2, 0, zx);
        matrix.set(2, 1, zy);

        return matrix;
    }

    Matrix view_transform(Tuple &from, Tuple &to, Tuple &up)
    {
        auto forward = (to - from).normalize();
        auto norm_up = up.normalize();
        auto left = forward.cross(norm_up);
        auto true_up = left.cross(forward);

        auto orientation = Matrix4x4(new double[16]{left.x, left.y, left.z, 0,
                                                    true_up.x, true_up.y, true_up.z, 0,
                                                    -forward.x, -forward.y, -forward.z, 0,
                                                    0, 0, 0, 1});

        return orientation * translation(-from.x, -from.y, -from.z);
    }
}