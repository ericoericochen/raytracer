#include <cassert>
#include <iostream>
#include "../include/world.h"
#include "../include/utils.h"
#include "../include/shapes/sphere.h"
#include "../include/shapes/plane.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/intersection.h"
#include "../include/prepared_computation.h"
#include "../include/light.h"

int main()
{
    World w = World();
    Ray r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    auto xs = w.intersects(r);

    std::cout << xs.size() << std::endl;

    assert(xs.size() == 4 && xs[0].t == 4.0 && xs[1].t == 4.5 && xs[2].t == 5.5 && xs[3].t == 6);

    // shading
    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    auto i = Intersection(w.objects[0], 4.0);
    auto comps = prepare_computation(i, r);
    // auto c = shade_hit(w, comps);
    auto c = w.shade_hit(comps);

    assert(c == Color(0.38066, 0.47583, 0.2855));

    // shading inside
    w = World();
    w.light = PointLight(tuple::point(0, 0.25, 0), Color(1, 1, 1));
    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    i = Intersection(w.objects[1], 0.5);
    comps = prepare_computation(i, r);
    c = w.shade_hit(comps);

    assert(c == Color(0.90498, 0.90498, 0.90498));

    // color at
    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 1, 0));
    c = w.color_at(r);

    assert(c == Color(0, 0, 0));

    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    c = w.color_at(r);

    assert(c == Color(0.38066, 0.47583, 0.2855));

    w = World();
    auto outer = w.objects[0];
    outer->material.ambient = 1;

    auto inner = w.objects[1];
    inner->material.ambient = 1;

    r = Ray(tuple::point(0, 0, 0.75), tuple::vec(0, 0, -1));
    c = w.color_at(r);

    assert(c == inner->material.color);

    // shadow
    w = World();
    auto p = tuple::point(0, 10, 0);
    assert(w.is_shadowed(p) == false);

    // The shadow when an object is between the point and the light
    p = tuple::point(10, -10, 10);
    assert(w.is_shadowed(p) == true);

    // There is no shadow when an object is behind the light
    p = tuple::point(-20, 20, -20);
    assert(w.is_shadowed(p) == false);

    // There is no shadow when an object is behind the point
    p = tuple::point(-2, 2, -2);
    assert(w.is_shadowed(p) == false);

    //
    w = World();
    w.light = PointLight(tuple::point(0, 0, -10), Color(1, 1, 1));
    auto s1 = Sphere();
    auto s2 = Sphere();
    s2.transform = matrix::translation(0, 0, 10);
    w.objects = {&s1, &s2};

    r = Ray(tuple::point(0, 0, 5), tuple::vec(0, 0, 1));
    i = Intersection(&s2, 4);
    comps = prepare_computation(i, r);
    c = w.shade_hit(comps);
    assert(c == Color(0.1, 0.1, 0.1));

    // The reflected color for a nonreflective material
    w = World();
    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    auto shape = w.objects[1];
    shape->material.ambient = 1;
    i = Intersection(shape, 1);
    comps = prepare_computation(i, r);
    c = w.reflected_color(comps);

    assert(c == Color(0, 0, 0));

    // The reflected color for a reflective material
    w = World();
    auto plane = Plane();
    plane.material.reflective = 0.5;
    plane.transform = transforms::translation(0, -1, 0);
    w.objects.push_back(&plane);
    r = Ray(tuple::point(0, 0, -3), tuple::vec(0, -sqrt(2) / 2, sqrt(2) / 2));
    i = Intersection(&plane, sqrt(2));
    comps = prepare_computation(i, r);
    c = w.reflected_color(comps);

    assert(c == Color(0.19032, 0.2379, 0.14274));

    // shade_hit() with a reflective material
    w = World();
    plane = Plane();
    plane.material.reflective = 0.5;
    plane.transform = transforms::translation(0, -1, 0);
    w.objects.push_back(&plane);
    r = Ray(tuple::point(0, 0, -3), tuple::vec(0, -sqrt(2) / 2, sqrt(2) / 2));
    i = Intersection(&plane, sqrt(2));
    comps = prepare_computation(i, r);
    c = w.shade_hit(comps);

    assert(c == Color(0.87677, 0.92436, 0.82918));

    // color_at() with mutually reflective surfaces
    w = World();
    w.light = PointLight(tuple::point(0, 0, 0), Color(1, 1, 1));
    auto lower = Plane();
    lower.material.reflective = 1;
    lower.transform = transforms::translation(0, -1, 0);
    auto upper = Plane();
    upper.material.reflective = 1;
    upper.transform = transforms::translation(0, 1, 0);
    w.objects = {&lower, &upper};
    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 1, 0));
    c = w.color_at(r);

    // The reflected color at the maximum recursive depth
    w = World();
    plane = Plane();
    plane.material.reflective = 0.5;
    plane.transform = transforms::translation(0, -1, 0);
    w.objects.push_back(&plane);
    r = Ray(tuple::point(0, 0, -3), tuple::vec(0, -sqrt(2) / 2, sqrt(2) / 2));
    i = Intersection(&plane, sqrt(2));
    comps = prepare_computation(i, r);
    c = w.reflected_color(comps, 0);
    assert(c == Color(0, 0, 0));
}
