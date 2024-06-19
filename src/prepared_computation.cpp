#include <iostream>
#include "../include/prepared_computation.h"
#include "../include/utils.h"
#include "../include/shapes/shape.h"

PreparedComputation::PreparedComputation(double t, Shape *object, Tuple point, Tuple eyev, Tuple normalv, bool inside, Tuple over_point)
    : t(t), object(object), point(point), eyev(eyev), normalv(normalv), inside(inside), over_point(over_point)
{
}

PreparedComputation prepare_computation(Intersection &intersection, Ray &ray)
{
    auto point = ray.position_at(intersection.t);
    auto eyev = -ray.direction;
    auto normalv = intersection.object->normal_at(point);
    bool inside = normalv.dot(eyev) < 0;

    if (inside)
    {
        normalv = normalv * -1;
    }

    auto over_point = point + normalv * EPSILON;
    return PreparedComputation(intersection.t, intersection.object, point, eyev, normalv, inside, over_point);
}