#include <cassert>
#include "../include/sphere.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/matrix.h"

int main()
{
    auto origin = tuple::point(0, 0, -5);
    auto direction = tuple::vec(0, 0, 1);
    auto r = Ray(origin, direction);
    auto s = Sphere();
    auto xs = s.intersects(r);

    assert(xs.size() == 2 && xs[0].t == 4.0 && xs[1].t == 6.0);

    origin = tuple::point(0, 2, -5);
    direction = tuple::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    xs = s.intersects(r);

    assert(xs.size() == 0);

    origin = tuple::point(0, 0, 0);
    direction = tuple::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    xs = s.intersects(r);

    assert(xs.size() == 2 && xs[0].t == -1.0 && xs[1].t == 1.0);

    origin = tuple::point(0, 0, 5);
    direction = tuple::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    xs = s.intersects(r);

    assert(xs.size() == 2 && xs[0].t == -6.0 && xs[1].t == -4.0);

    // sphere transform
    s = Sphere();
    Matrix t = matrix::translation(2, 3, 4);
    s.set_transform(t);
    assert(s.transform == t);

    // ray sphere intersection with scaled sphere
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s = Sphere();
    s.set_transform(matrix::scaling(2, 2, 2));
    xs = s.intersects(r);
    assert(xs.size() == 2 && xs[0].t == 3 && xs[1].t == 7);

    // ray sphere intersection with translated sphere
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s = Sphere();
    s.set_transform(matrix::translation(5, 0, 0));
    xs = s.intersects(r);
    assert(xs.size() == 0);
}