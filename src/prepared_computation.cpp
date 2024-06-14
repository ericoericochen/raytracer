#include "../include/prepared_computation.h"
#include <iostream>

PreparedComputation::PreparedComputation(double t, Sphere *object, Tuple point, Tuple eyev, Tuple normalv, bool inside)
    : t(t), object(object), point(point), eyev(eyev), normalv(normalv), inside(inside)
{
}

PreparedComputation prepare_computation(Intersection &intersection, Ray &ray)
{
    std::cout << intersection.t << std::endl;

    auto point = ray.position_at(intersection.t);
    auto eyev = -ray.direction;
    auto normalv = intersection.object->normal_at(point);

    bool inside = normalv.dot(eyev) < 0;

    if (inside)
    {
        normalv = normalv * -1;
    }

    return PreparedComputation(intersection.t, intersection.object, point, eyev, normalv, inside);
}