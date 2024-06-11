#ifndef MATRIX_H
#define MATRIX_H

#include "tuple.h"

class Ray
{
public:
    Tuple origin;
    Tuple direction;
    Ray(Tuple origin, Tuple direction);
    Tuple position_at(double t) const;
};

#endif