#include <cassert>
#include <iostream>
#include "../../include/shapes/cylinder.h"
#include "../../include/ray.h"
#include "../../include/tuple.h"
#include "../../include/utils.h"

int main()
{
    // A ray misses a cylinder
    auto cyl = Cylinder();
    auto ray = Ray(tuple::point(1, 0, 0), tuple::vec(0, 1, 0));
    auto xs = cyl.intersects(ray);

    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 0, 0), tuple::vec(0, 1, 0));
    xs = cyl.intersects(ray);

    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 0, -5), tuple::vec(1, 1, 1));
    xs = cyl.intersects(ray);

    assert(xs.size() == 0);

    // A ray strikes a cylinder
    ray = Ray(tuple::point(1, 0, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);

    assert(xs.size() == 2);
    assert(xs[0].t == 5);
    assert(xs[1].t == 5);

    // A ray strikes a cylinder from the side
    ray = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);

    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    // A ray strikes a cylinder's end caps
    ray = Ray(tuple::point(0.5, 0, -5), tuple::vec(0.1, 1, 1).normalize());
    xs = cyl.intersects(ray);

    assert(xs.size() == 2);
    assert(equal(xs[0].t, 6.80798));
    assert(equal(xs[1].t, 7.08872));

    // Normal vector on a cylinder
    auto n = cyl.normal_at(tuple::point(1, 0, 0));
    assert(n == tuple::vec(1, 0, 0));

    n = cyl.normal_at(tuple::point(0, 5, -1));
    assert(n == tuple::vec(0, 0, -1));

    n = cyl.normal_at(tuple::point(0, -2, 1));
    assert(n == tuple::vec(0, 0, 1));

    n = cyl.normal_at(tuple::point(-1, 1, 0));
    assert(n == tuple::vec(-1, 0, 0));

    // Intersecting a constrained cylinder
    cyl = Cylinder(1, 2);

    ray = Ray(tuple::point(0, 1.5, 0), tuple::vec(0.1, 1, 0).normalize());
    xs = cyl.intersects(ray);
    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 3, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);
    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);
    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 2, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);
    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 1, -5), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);
    assert(xs.size() == 0);

    ray = Ray(tuple::point(0, 1.5, -2), tuple::vec(0, 0, 1));
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    // Intersecting the caps of a closed cylinder
    cyl = Cylinder(1, 2, true);

    ray = Ray(tuple::point(0, 3, 0), tuple::vec(0, -1, 0));
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    ray = Ray(tuple::point(0, 3, -2), tuple::vec(0, -1, 2).normalize());
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    ray = Ray(tuple::point(0, 4, -2), tuple::vec(0, -1, 1).normalize());
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    ray = Ray(tuple::point(0, 0, -2), tuple::vec(0, 1, 2).normalize());
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    ray = Ray(tuple::point(0, -1, -2), tuple::vec(0, 1, 1).normalize());
    xs = cyl.intersects(ray);
    assert(xs.size() == 2);

    //  The normal vector on a cylinder's end caps
    n = cyl.normal_at(tuple::point(0, 1, 0));
    assert(n == tuple::vec(0, -1, 0));

    n = cyl.normal_at(tuple::point(0.5, 1, 0));
    assert(n == tuple::vec(0, -1, 0));

    n = cyl.normal_at(tuple::point(0, 1, 0.5));
    assert(n == tuple::vec(0, -1, 0));

    n = cyl.normal_at(tuple::point(0, 2, 0));
    assert(n == tuple::vec(0, 1, 0));

    n = cyl.normal_at(tuple::point(0.5, 2, 0));
    assert(n == tuple::vec(0, 1, 0));

    n = cyl.normal_at(tuple::point(0, 2, 0.5));
    assert(n == tuple::vec(0, 1, 0));
}