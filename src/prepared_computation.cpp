#include <iostream>
#include "../include/prepared_computation.h"
#include "../include/utils.h"
#include "../include/shapes/shape.h"

PreparedComputation::PreparedComputation(double t, Shape *object, Tuple point, Tuple eyev,
                                         Tuple normalv, bool inside, Tuple over_point,
                                         Tuple reflectv, double n1, double n2, Tuple under_point)
    : t(t), object(object), point(point), eyev(eyev), normalv(normalv), inside(inside), over_point(over_point), reflectv(reflectv),
      n1(n1), n2(n2), under_point(under_point)
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
    auto reflectv = tuple::reflect(ray.direction, normalv);
    return PreparedComputation(intersection.t, intersection.object, point, eyev, normalv, inside, over_point, reflectv);
}

PreparedComputation prepare_computation(Intersection &intersection, Ray &ray, std::vector<Intersection> &xs)
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
    auto under_point = point - normalv * EPSILON;
    auto reflectv = tuple::reflect(ray.direction, normalv);

    double n1 = 1.0;
    double n2 = 1.0;
    std::vector<Shape *> containers = {};

    for (int i = 0; i < xs.size(); i++)
    {
        if (&xs[i] == &intersection)
        {
            if (containers.empty())
            {
                n1 = 1.0;
            }
            else
            {
                n1 = containers.back()->material.refractive_index;
            }
        }

        // check if the object is in the containers list
        if (std::find(containers.begin(), containers.end(), xs[i].object) != containers.end())
        {
            containers.erase(std::remove(containers.begin(), containers.end(), xs[i].object), containers.end());
        }
        else
        {
            containers.push_back(xs[i].object);
        }

        if (&xs[i] == &intersection)
        {
            if (containers.empty())
            {
                n2 = 1.0;
            }
            else
            {
                n2 = containers.back()->material.refractive_index;
            }

            break;
        }
    }

    return PreparedComputation(intersection.t, intersection.object, point, eyev, normalv, inside, over_point, reflectv, n1, n2, under_point);
}
