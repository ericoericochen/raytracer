#include <iostream>
#include "../../include/shapes/shape.h"

Shape::Shape() {}

std::vector<Intersection> Shape::intersects(Ray &ray)
{
    // convert ray to object space by multiplying it with the inverse transform
    // transform takes something from object space to world space
    // inverse tranform takes something from world space to object space

    auto inv_transform = this->transform.inverse();
    Ray local_ray = ray::transform(ray, inv_transform);
    return this->local_intersects(local_ray);
}

std::vector<Intersection> Shape::local_intersects(Ray &local_ray)
{
    this->saved_ray = local_ray;

    return std::vector<Intersection>();
}

Tuple Shape::normal_at(const Tuple &world_point) const
{
    // convert point to object space
    auto inv_transform = this->transform.inverse();
    auto local_point = inv_transform * world_point;

    // get local normal
    auto local_normal = this->local_normal_at(local_point);
    auto world_normal = inv_transform.T() * local_normal;
    world_normal.w = 0;
    auto normal = world_normal.normalize();

    return normal;
}

Tuple Shape::local_normal_at(const Tuple &world_point) const
{
    return tuple::vec(world_point.x, world_point.y, world_point.z);
}

Color Shape::pattern_at(const Tuple &world_point) const
{
    auto object_point = this->transform.inverse() * world_point;
    auto pattern_point = this->material.pattern->transform.inverse() * object_point;

    return this->material.pattern->pattern_at(pattern_point);
}
