#include <cassert>
#include "../include/ray.h"
#include "../include/tuple.h"

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
