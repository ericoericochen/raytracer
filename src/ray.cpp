#include <cassert>
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/matrix.h"

Ray::Ray(Tuple origin, Tuple direction)
{
    assert(origin.is_point() && direction.is_vector());
    this->origin = origin;
    this->direction = direction;
}

Tuple Ray::position_at(double t) const
{
    return this->origin + this->direction * t;
}

namespace ray
{
    Ray transform(Ray &ray, Matrix &matrix)
    {
        return Ray(matrix * ray.origin, matrix * ray.direction);
    }
}
