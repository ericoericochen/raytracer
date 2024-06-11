#include <cassert>
#include "../include/tuple.h"
#include "../include/ray.h"
#include "../include/sphere.h"

int main()
{
    Tuple origin = tuple::point(1, 2, 3);
    Tuple direction = tuple::vec(4, 5, 6);
    Ray r = Ray(origin, direction);

    assert(r.origin == origin && r.direction == direction);

    // position at
    r = Ray(tuple::point(2, 3, 4), tuple::vec(1, 0, 0));
    assert(r.position_at(0) == tuple::point(2, 3, 4));
    assert(r.position_at(1) == tuple::point(3, 3, 4));
    assert(r.position_at(-1) == tuple::point(1, 3, 4));
    assert(r.position_at(2.5) == tuple::point(4.5, 3, 4));

    // ray sphere intersection
    Sphere s;

    origin = tuple::point(0, 0, -5);
    direction = tuple::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    // Intersection intersection = s.intersects(r);
    // assert(intersection.count() == 2 && intersection[0] == 4.0 && intersection[1] == 6.0);

    // origin = tuple::point(0, 1, -5);
    // direction = tuple::vec(0, 0, 1);
    // r = Ray(origin, direction);
    // s = Sphere();
    // Intersection intersection = s.intersects(r);
    // assert(intersection.count() == 2 && intersection[0] == 5.0 && intersection[1] == 5.0);

    // origin = tuple::point(0, 2, -5);
    // direction = tuple::vec(0, 0, 1);
    // r = Ray(origin, direction);
    // s = Sphere();
    // Intersection intersection = s.intersects(r);
    // assert(intersection.count() == 0);

    // origin = tuple::point(0, 0, 0);
    // direction = tuple::vec(0, 0, 1);
    // r = Ray(origin, direction);
    // s = Sphere();
    // Intersection intersection = s.intersects(r);
    // assert(intersection.count() == 2 && intersection[0] == -1.0 && intersection[1] == 1.0);
}