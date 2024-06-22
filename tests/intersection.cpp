#include <cassert>
#include <vector>
#include <iostream>
#include "../include/intersection.h"
#include "../include/shapes/sphere.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/utils.h"
#include "../include/prepared_computation.h"
#include "../include/shapes/plane.h"

int main()
{
    Sphere s = Sphere();
    Intersection i = Intersection(&s, 3);

    assert(i.object == &s && i.t == 3);

    s = Sphere();
    auto i1 = Intersection(&s, 1);
    auto i2 = Intersection(&s, 2);
    std::vector<Intersection> xs = {i1, i2};
    auto i_ = intersection::hit(xs);

    assert(i_.value() == &xs[0]);

    s = Sphere();
    i1 = Intersection(&s, -1);
    i2 = Intersection(&s, 1);
    xs = {i1, i2};
    i_ = intersection::hit(xs);

    assert(i_.value() == &xs[1]);

    s = Sphere();
    i1 = Intersection(&s, -1);
    i2 = Intersection(&s, -2);
    xs = {i1, i2};
    i_ = intersection::hit(xs);

    assert(!i_.has_value());

    s = Sphere();
    i1 = Intersection(&s, 5);
    i2 = Intersection(&s, 7);
    auto i3 = Intersection(&s, -3);
    auto i4 = Intersection(&s, 2);
    xs = {i1, i2, i3, i4};
    i_ = intersection::hit(xs);

    assert(i_.value() == &xs[3]);

    Ray r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    Sphere shape = Sphere();
    i = Intersection(&shape, 4);
    auto comps = prepare_computation(i, r);

    assert(comps.t == i.t && !comps.inside && comps.object == i.object && comps.point == tuple::point(0, 0, -1) && comps.eyev == tuple::vec(0, 0, -1) && comps.normalv == tuple::vec(0, 0, -1));

    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    shape = Sphere();
    i = Intersection(&shape, 1);
    comps = prepare_computation(i, r);

    assert(comps.point == tuple::point(0, 0, 1) && comps.eyev == tuple::vec(0, 0, -1) && comps.inside && comps.normalv == tuple::vec(0, 0, -1));

    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    shape = Sphere();
    shape.transform = matrix::translation(0, 0, 1);
    i = Intersection(&shape, 5);
    comps = prepare_computation(i, r);

    assert(comps.over_point.z < -EPSILON / 2 && comps.point.z > comps.over_point.z);

    // Precomputing the reflection vector
    auto plane = Plane();
    r = Ray(tuple::point(0, 1, -1), tuple::vec(0, -sqrt(2) / 2, sqrt(2) / 2));
    i = Intersection(&plane, sqrt(2));
    comps = prepare_computation(i, r);

    assert(comps.reflectv == tuple::vec(0, sqrt(2) / 2, sqrt(2) / 2));
}