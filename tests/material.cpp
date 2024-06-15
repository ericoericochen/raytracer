#include <cassert>
#include <iostream>
#include "../include/material.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/tuple.h"

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

    Color result = lighting(m, light, position, eyev, normalv);
    assert(result == Color(1.9, 1.9, 1.9));

    eyev = tuple::vec(0, sqrt(2) / 2, -sqrt(2) / 2);
    normalv = tuple::vec(0, 0, -1);
    result = lighting(m, light, position, eyev, normalv);
    assert(result == Color(1.0, 1.0, 1.0));

    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 10, -10), Color(1, 1, 1));
    result = lighting(m, light, position, eyev, normalv);
    assert(result == Color(0.7364, 0.7364, 0.7364));

    eyev = tuple::vec(0, -sqrt(2) / 2, -sqrt(2) / 2);
    normalv = tuple::vec(0, 0, -1);
    result = lighting(m, light, position, eyev, normalv);
    assert(result == Color(1.6364, 1.6364, 1.6364));

    eyev = tuple::vec(0, 0, -1);
    normalv = tuple::vec(0, 0, -1);
    light = PointLight(tuple::point(0, 0, 10), Color(1, 1, 1));
    result = lighting(m, light, position, eyev, normalv);
    assert(result == Color(0.1, 0.1, 0.1));
}