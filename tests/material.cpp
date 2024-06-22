#include <cassert>
#include <iostream>
#include "../include/material.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/tuple.h"
#include "../include/patterns/stripe.h"
#include "../include/shapes/shape.h"
#include "../include/shapes/sphere.h"

int main()
{
    Material m = Material();
    assert(m.ambient == 0.1 && m.diffuse == 0.9 && m.specular == 0.9 && m.shininess == 200.0);

    Material m2 = Material();
    m2.color = Color(1, 1, 1);
    m2.ambient = 0.2;
    m2.diffuse = 0.3;
    m2.specular = 0.4;
    m2.shininess = 0.5;
    assert(m2.ambient == 0.2 && m2.diffuse == 0.3 && m2.specular == 0.4 && m2.shininess == 0.5);

    // lighting
    m = Material();
    Tuple position = tuple::point(0, 0, 0);
    Tuple eyev = tuple::vec(0, 0, -1);
    Tuple normalv = tuple::vec(0, 0, -1);
    PointLight light = PointLight(tuple::point(0, 0, -10), Color(1, 1, 1));

    Color result = lighting(m, nullptr, light, position, eyev, normalv);
    assert(result == Color(1.9, 1.9, 1.9));

    eyev = tuple::vec(0, sqrt(2) / 2, -sqrt(2) / 2);
    normalv = tuple::vec(0, 0, -1);
    result = lighting(m, nullptr, light, position, eyev, normalv);
    assert(result == Color(1.0, 1.0, 1.0));

    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 10, -10), Color(1, 1, 1));
    result = lighting(m, nullptr, light, position, eyev, normalv);
    assert(result == Color(0.7364, 0.7364, 0.7364));

    eyev = tuple::vec(0, -sqrt(2) / 2, -sqrt(2) / 2);
    normalv = tuple::vec(0, 0, -1);
    result = lighting(m, nullptr, light, position, eyev, normalv);
    assert(result == Color(1.6364, 1.6364, 1.6364));

    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 0, 10), Color(1, 1, 1));
    result = lighting(m, nullptr, light, position, eyev, normalv);
    assert(result == Color(0.1, 0.1, 0.1));

    // shadows
    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 0, -10), Color(1, 1, 1));
    bool in_shadow = true;
    result = lighting(m, nullptr, light, position, eyev, normalv, in_shadow);

    assert(result == Color(0.1, 0.1, 0.1));

    // Lighting with a pattern applied
    auto s = Sphere();
    auto p = Stripe(Color(1, 1, 1), Color(0, 0, 0));

    m = Material();
    m.pattern = &p;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    s.material = m;
    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 0, -10), Color(1, 1, 1));

    auto c1 = lighting(m, &s, light, tuple::point(0.9, 0, 0), eyev, normalv, false);
    auto c2 = lighting(m, &s, light, tuple::point(1.1, 0, 0), eyev, normalv, false);

    assert(c1 == Color(1, 1, 1));
    assert(c2 == Color(0, 0, 0));

    // Reflectivity for the default material
    m = Material();
    assert(m.reflective == 0.0);

    // Transparency and Refractive Index for the default material
    m = Material();
    assert(m.transparency == 0.0 && m.refractive_index == 1.0);

    // Glassy sphere
    auto s2 = glass_sphere();
    assert(s2.material.transparency == 1.0 && s2.material.refractive_index == 1.5);
}