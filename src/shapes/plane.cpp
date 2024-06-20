#include <cassert>
#include <vector>
#include <iostream>
#include "../../include/shapes/plane.h"
#include "../../include/ray.h"
#include "../../include/tuple.h"
#include "../../include/intersection.h"
#include "../../include/utils.h"

Plane::Plane() {}

std::vector<Intersection> Plane::local_intersects(Ray &local_ray)
{
    if (abs(local_ray.direction.y) < EPSILON) {
        return std::vector<Intersection>();
    }

    auto t = -local_ray.origin.y / local_ray.direction.y;   

    return std::vector<Intersection>{Intersection(this, t)};
}

Tuple Plane::local_normal_at(const Tuple &local_point) const
{
    return tuple::vec(0, 1, 0);
}
