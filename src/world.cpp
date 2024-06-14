#include <vector>
#include <algorithm>
#include <iostream>
#include "../include/world.h"
#include "../include/light.h"
#include "../include/sphere.h"
#include "../include/material.h"
#include "../include/color.h"
#include "../include/matrix.h"
#include "../include/ray.h"

World::World()
{
    // default light
    this->light = light::point_light(
        tuple::point(-10, 10, -10), Color(1, 1, 1));

    // default objects
    Sphere s1 = Sphere(Material(Color(0.8, 1.0, 0.6), 0.7, 0.2));
    Sphere s2 = Sphere();
    s2.set_transform(matrix::scaling(0.5, 0.5, 0.5));

    std::vector<Sphere> default_objects = {s1, s2};
    this->objects = default_objects;
}

std::vector<Intersection> World::intersects(Ray &ray)
{
    std::vector<Intersection> intersections = {};

    // for each object, calculate intersections
    for (auto &object : this->objects)
    {
        auto object_intersections = object.intersects(ray);
        intersections.insert(intersections.end(), object_intersections.begin(), object_intersections.end());
    }

    // sort intersections by t
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b)
              { return a.t < b.t; });

    return intersections;
}