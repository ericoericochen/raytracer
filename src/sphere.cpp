#include <cassert>
#include <vector>
#include "../include/sphere.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/intersection.h"

Sphere::Sphere() {}

void Sphere::set_transform(const Matrix &matrix) { this->transform = matrix; }

std::vector<Intersection> Sphere::intersects(Ray &ray)
{
    // apply the inverse transform of sphere to the ray
    auto inv_transform = this->transform.inverse();
    Ray transformed_ray = ray::transform(ray, inv_transform);

    Tuple sphere_to_ray = transformed_ray.origin - tuple::point(0, 0, 0); // ray origin - sphere origin
    double a = transformed_ray.direction.dot(transformed_ray.direction);
    double b = 2.0 * transformed_ray.direction.dot(sphere_to_ray);
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

Tuple Sphere::normal_at(const Tuple &world_point) const
{
    auto object_point = this->transform.inverse() * world_point;
    auto object_normal = object_point - tuple::point(0, 0, 0);
    Tuple world_normal = this->transform.inverse().T() * object_normal;
    world_normal.w = 0;

    return world_normal.normalize();
}
