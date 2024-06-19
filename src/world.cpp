#include <vector>
#include <algorithm>
#include <iostream>
#include "../include/world.h"
#include "../include/light.h"
#include "../include/shapes/shape.h"
#include "../include/shapes/sphere.h"
#include "../include/material.h"
#include "../include/color.h"
#include "../include/matrix.h"
#include "../include/ray.h"
#include "../include/canvas.h"
#include "../include/camera.h"

World::World()
{
    // default light
    this->light = light::point_light(
        tuple::point(-10, 10, -10), Color(1, 1, 1));

    // default objects
    Material m = Material();
    m.color = Color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;

    Sphere s1 = Sphere();
    s1.material = m;

    Sphere s2 = Sphere();
    s2.transform = matrix::scaling(0.5, 0.5, 0.5);

    std::vector<Shape *> default_objects = {&s1, &s2};
    this->objects = default_objects;
}

std::vector<Intersection> World::intersects(Ray &ray)
{
    std::vector<Intersection> intersections = {};

    // for each object, calculate intersections
    for (auto &object : this->objects)
    {
        auto object_intersections = object->intersects(ray);
        intersections.insert(intersections.end(), object_intersections.begin(), object_intersections.end());
    }

    // sort intersections by t
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b)
              { return a.t < b.t; });

    return intersections;
}

Color World::shade_hit(PreparedComputation &comps)
{
    bool in_shadow = this->is_shadowed(comps.over_point);
    return lighting(
        comps.object->material,
        this->light,
        comps.over_point,
        comps.eyev,
        comps.normalv,
        in_shadow);
}

Color World::color_at(Ray &ray)
{
    auto intersections = this->intersects(ray);
    auto hit = intersection::hit(intersections);

    if (!hit.has_value())
    {
        return Color(0, 0, 0);
    }

    PreparedComputation comps = prepare_computation(*hit.value(), ray);
    return this->shade_hit(comps);
}

Canvas World::render(Camera &camera)
{
    Canvas canvas = Canvas(camera.hsize, camera.vsize);

    // loop through every pixel of canvas
    for (int y = 0; y < canvas.height(); y++)
    {
        for (int x = 0; x < canvas.width(); x++)
        {
            // get ray going from camera to pixel in world space
            Ray ray = camera.ray_for_pxiel(x, y);
            Color color = this->color_at(ray);
            canvas.write_pixel(x, y, color);
        }
    }

    return canvas;
}

bool World::is_shadowed(Tuple &point)
{
    auto point_to_light = this->light.position - point;
    auto distance = point_to_light.magnitude();
    auto direction = point_to_light.normalize();

    Ray ray = Ray(point, direction);
    auto intersections = this->intersects(ray);
    auto hit = intersection::hit(intersections);

    if (!hit.has_value())
    {
        return false;
    }

    auto hit_value = hit.value();

    return hit_value->t < distance;
}