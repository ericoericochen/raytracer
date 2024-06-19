#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"

namespace transforms
{
    Matrix eye();
    Matrix translation(double x, double y, double z);
    Matrix scaling(double x, double y, double z);
    Matrix rotation_x(double radians);
    Matrix rotation_y(double radians);
    Matrix rotation_z(double radians);
    Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy);
    Matrix view_transform(Tuple &from, Tuple &to, Tuple &up);
}

#endif