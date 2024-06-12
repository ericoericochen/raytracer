#include <cassert>
#include <vector>
#include "../include/sphere.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/intersection.h"

Sphere::Sphere() {}
Sphere::Sphere(Tuple origin, double radius)
{
    assert(origin.is_point() && radius > 0);
    this->origin = origin;
    this->radius = radius;
}

namespace sphere
{
    std::vector<Intersection> intersects(Sphere &sphere, Ray &ray)
    {
        Tuple sphere_to_ray = ray.origin - sphere.origin;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * ray.direction.dot(sphere_to_ray);
        double c = sphere_to_ray.dot(sphere_to_ray) - sphere.radius * sphere.radius;

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

        intersections.push_back(Intersection(&sphere, x1));
        intersections.push_back(Intersection(&sphere, x2));

        return intersections;
    }

}