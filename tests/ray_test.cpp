#include <cassert>
#include "../include/tuple.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/matrix.h"

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

    // ray transform
    r = Ray(tuple::point(1, 2, 3), tuple::vec(0, 1, 0));
    Matrix m = matrix::translation(3, 4, 5);
    Ray r2 = ray::transform(r, m);

    assert(r2.origin == tuple::point(4, 6, 8) && r2.direction == tuple::vec(0, 1, 0));

    r = Ray(tuple::point(1, 2, 3), tuple::vec(0, 1, 0));
    m = matrix::scaling(2, 3, 4);
    r2 = ray::transform(r, m);

    assert(r2.origin == tuple::point(2, 6, 12) && r2.direction == tuple::vec(0, 3, 0));
}