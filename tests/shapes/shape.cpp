#include <cassert>
#include <iostream>
#include "../../include/shapes/shape.h"
#include "../../include/transforms.h"
#include "../../include/ray.h"
#include "../../include/tuple.h"

int main()
{
    Shape s = Shape();
    assert(s.transform == transforms::eye());

    s.transform = transforms::translation(2, 3, 4);
    assert(s.transform == transforms::translation(2, 3, 4));

    // Intersecting a scaled shape with a ray
    Ray r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s.transform = transforms::scaling(2, 2, 2);
    auto xs = s.intersects(r);

    assert(s.saved_ray.origin == tuple::point(0, 0, -2.5));
    assert(s.saved_ray.direction == tuple::vec(0, 0, 0.5));

    //  Intersecting a translated shape with a ray
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s.transform = transforms::translation(5, 0, 0);
    xs = s.intersects(r);

    assert(s.saved_ray.origin == tuple::point(-5, 0, -5));
    assert(s.saved_ray.direction == tuple::vec(0, 0, 1));

    // Computing the normal on a translated shape
    s.transform = transforms::translation(0, 1, 0);
    auto n = s.normal_at(tuple::point(0, 1.70711, -0.70711));
    assert(n == tuple::vec(0, 0.70711, -0.70711));

    // Computing the normal on a transformed shape
    s.transform = transforms::scaling(1, 0.5, 1) * transforms::rotation_z(M_PI / 5);
    n = s.normal_at(tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));
    assert(n == tuple::vec(0, 0.97014, -0.24254));
}