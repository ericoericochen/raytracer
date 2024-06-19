#include <cassert>
#include "../../include/shapes/sphere.h"
#include "../../include/ray.h"
#include "../../include/tuple.h"
#include "../../include/matrix.h"

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
    s.transform = t;
    assert(s.transform == t);

    // ray sphere intersection with scaled sphere
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s = Sphere();
    s.transform = matrix::scaling(2, 2, 2);
    xs = s.intersects(r);
    assert(xs.size() == 2 && xs[0].t == 3 && xs[1].t == 7);

    // ray sphere intersection with translated sphere
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    s = Sphere();
    s.transform = matrix::translation(5, 0, 0);
    xs = s.intersects(r);
    assert(xs.size() == 0);

    // normals
    s = Sphere();
    auto n = s.normal_at(tuple::point(1, 0, 0));
    assert(n == tuple::vec(1, 0, 0));

    n = s.normal_at(tuple::point(0, 1, 0));
    assert(n == tuple::vec(0, 1, 0));

    n = s.normal_at(tuple::point(0, 0, 1));
    assert(n == tuple::vec(0, 0, 1));

    n = s.normal_at(tuple::point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    assert(n == tuple::vec(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    s.transform = matrix::translation(0, 1, 0);
    n = s.normal_at(tuple::point(0, 1.70711, -0.70711));
    assert(n == tuple::vec(0, 0.70711, -0.70711));

    s.transform = matrix::scaling(1, 0.5, 1) * matrix::rotation_z(M_PI / 5);
    n = s.normal_at(tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));
    assert(n == tuple::vec(0, 0.97014, -0.24254));
}