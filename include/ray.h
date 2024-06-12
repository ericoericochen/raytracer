#ifndef RAY_H
#define RAY_H

#include "tuple.h"
#include "matrix.h"

class Ray
{
public:
    Tuple origin;
    Tuple direction;
    Ray(Tuple origin, Tuple direction);
    Tuple position_at(double t) const;
};

namespace ray
{
    Ray transform(Ray &ray, Matrix &matrix);
}

#endif