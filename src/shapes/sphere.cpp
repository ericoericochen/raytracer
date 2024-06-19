#include <cassert>
#include <vector>
#include <iostream>
#include "../../include/shapes/sphere.h"
#include "../../include/ray.h"
#include "../../include/tuple.h"
#include "../../include/intersection.h"

Sphere::Sphere() {}

std::vector<Intersection> Sphere::local_intersects(Ray &local_ray)
{
    // std::cout << "Sphere::local_intersects" << std::endl;

    Tuple sphere_to_ray = local_ray.origin - tuple::point(0, 0, 0); // ray origin - sphere origin
    double a = local_ray.direction.dot(local_ray.direction);
    double b = 2.0 * local_ray.direction.dot(sphere_to_ray);
    double c = sphere_to_ray.dot(sphere_to_ray) - 1; // -radius^2
    double discriminant = b * b - 4 * a * c;

    std::vector<Intersection> intersections = {};

    // no intersections
    if (discriminant < 0)
    {
        return intersections;
    }

    // calculate the two intersections
    auto x1 = (-b - sqrt(discriminant)) / (2 * a);
    auto x2 = (-b + sqrt(discriminant)) / (2 * a);

    intersections.push_back(Intersection(this, x1));
    intersections.push_back(Intersection(this, x2));

    return intersections;
}

Tuple Sphere::local_normal_at(const Tuple &local_point) const
{
    auto local_normal = local_point - tuple::point(0, 0, 0);
    return local_normal;
}
