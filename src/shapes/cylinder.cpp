#include <vector>
#include "../../include/utils.h"
#include "../../include/shapes/cylinder.h"
#include "../../include/intersection.h"
#include "../../include/utils.h"

Cylinder::Cylinder() {}

Cylinder::Cylinder(double min, double max, bool closed) : min(min), max(max), closed(closed) {}

bool check_cap(Ray &ray, double t)
{
    auto x = ray.origin.x + t * ray.direction.x;
    auto z = ray.origin.z + t * ray.direction.z;

    return (x * x + z * z) <= 1;
}

std::vector<Intersection> Cylinder::intersect_caps(Ray &ray)
{
    if (!this->closed || equal(ray.direction.y, 0))
    {
        return {};
    }

    std::vector<Intersection> intersections = {};

    // check lower end cap
    double t;
    t = (this->min - ray.origin.y) / ray.direction.y;

    if (check_cap(ray, t))
    {
        intersections.push_back(Intersection(this, t));
    }

    // check upper end cap
    t = (this->max - ray.origin.y) / ray.direction.y;

    if (check_cap(ray, t))
    {
        intersections.push_back(Intersection(this, t));
    }

    return intersections;
}

std::vector<Intersection> Cylinder::local_intersects(Ray &local_ray)
{
    auto a = local_ray.direction.x * local_ray.direction.x + local_ray.direction.z * local_ray.direction.z;

    if (equal(a, 0))
    {
        // return {};
        return this->intersect_caps(local_ray);
    }

    auto b = 2 * local_ray.origin.x * local_ray.direction.x + 2 * local_ray.origin.z * local_ray.direction.z;
    auto c = local_ray.origin.x * local_ray.origin.x + local_ray.origin.z * local_ray.origin.z - 1;

    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return {};
    }

    std::vector<Intersection> intersections = {};

    auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + sqrt(discriminant)) / (2 * a);

    auto y1 = local_ray.origin.y + t1 * local_ray.direction.y;

    if (this->min < y1 && y1 < this->max)
    {
        intersections.push_back(Intersection(this, t1));
    }

    auto y2 = local_ray.origin.y + t2 * local_ray.direction.y;

    if (this->min < y2 && y2 < this->max)
    {
        intersections.push_back(Intersection(this, t2));
    }

    auto cap_intersections = this->intersect_caps(local_ray);
    intersections.insert(intersections.end(), cap_intersections.begin(), cap_intersections.end());

    return intersections;
}

Tuple Cylinder::local_normal_at(const Tuple &local_point) const
{
    auto dist = local_point.x * local_point.x + local_point.z * local_point.z;

    if (dist < 1 && local_point.y >= this->max - EPSILON)
    {
        return tuple::vec(0, 1, 0);
    }
    else if (dist < 1 && local_point.y <= this->min + EPSILON)
    {
        return tuple::vec(0, -1, 0);
    }

    return tuple::vec(local_point.x, 0, local_point.z);
}