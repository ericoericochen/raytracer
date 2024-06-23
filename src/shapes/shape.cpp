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
    auto local_point = this->world_to_object(world_point);
    auto local_normal = this->local_normal_at(local_point);
    auto world_normal = this->normal_to_world(local_normal);

    return world_normal;
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

Tuple Shape::world_to_object(const Tuple &point) const
{
    Tuple object_point;

    if (this->parent != nullptr)
    {
        object_point = this->parent->world_to_object(point); // convert point to object space of parent
    }
    else
    {
        object_point = point;
    }

    // convert point from object space of parent to object space of this object
    return this->transform.inverse() * object_point;
}

Tuple Shape::normal_to_world(const Tuple &normal) const
{
    auto object_normal = this->transform.inverse().T() * normal;
    object_normal.w = 0;
    auto object_normal_norm = object_normal.normalize();

    Tuple world_normal;
    if (this->parent != nullptr)
    {
        world_normal = this->parent->normal_to_world(object_normal_norm);
    }
    else
    {
        world_normal = object_normal_norm;
    }

    return world_normal;
}
