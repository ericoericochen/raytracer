#include "../../include/shapes/cube.h"

int main()
{
    // A ray intersects a cube
    auto c = Cube();

    // | | origin | direction | t1 | t2 |
    // | +x | point(5, 0.5, 0) | vector(-1, 0, 0) | 4 | 6 |
    // | -x | point(-5, 0.5, 0) | vector(1, 0, 0) | 4 | 6 |
    // | +y | point(0.5, 5, 0) | vector(0, -1, 0) | 4 | 6 |
    // | -y | point(0.5, -5, 0) | vector(0, 1, 0) | 4 | 6 |
    // | +z | point(0.5, 0, 5) | vector(0, 0, -1) | 4 | 6 |
    // | -z | point(0.5, 0, -5) | vector(0, 0, 1) | 4 | 6 |
    // | inside | point(0, 0.5, 0) | vector(0, 0, 1) | -1 | 1 |

    auto r = Ray(tuple::point(5, 0.5, 0), tuple::vec(-1, 0, 0));
    auto xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(-5, 0.5, 0), tuple::vec(1, 0, 0));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(0.5, 5, 0), tuple::vec(0, -1, 0));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(0.5, -5, 0), tuple::vec(0, 1, 0));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(0.5, 0, 5), tuple::vec(0, 0, -1));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(0.5, 0, -5), tuple::vec(0, 0, 1));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == 4);
    assert(xs[1].t == 6);

    r = Ray(tuple::point(0, 0.5, 0), tuple::vec(0, 0, 1));
    xs = c.local_intersects(r);
    assert(xs.size() == 2);
    assert(xs[0].t == -1);
    assert(xs[1].t == 1);

    // A ray misses a cube

    //  The normal on the surface of a cube
    //     | point | normal |
    // | point(1, 0.5, -0.8) | vector(1, 0, 0) |
    // | point(-1, -0.2, 0.9) | vector(-1, 0, 0) |
    // | point(-0.4, 1, -0.1) | vector(0, 1, 0) |
    // | point(0.3, -1, -0.7) | vector(0, -1, 0) |
    // | point(-0.6, 0.3, 1) | vector(0, 0, 1) |
    // | point(0.4, 0.4, -1) | vector(0, 0, -1) |
    // | point(1, 1, 1) | vector(1, 0, 0) |
    // | point(-1, -1, -1) | vector(-1, 0, 0) |

    auto n = c.local_normal_at(tuple::point(1, 0.5, -0.8));
    assert(n == tuple::vec(1, 0, 0));

    n = c.local_normal_at(tuple::point(-1, -0.2, 0.9));
    assert(n == tuple::vec(-1, 0, 0));

    n = c.local_normal_at(tuple::point(-0.4, 1, -0.1));
    assert(n == tuple::vec(0, 1, 0));

    n = c.local_normal_at(tuple::point(0.3, -1, -0.7));
    assert(n == tuple::vec(0, -1, 0));

    n = c.local_normal_at(tuple::point(-0.6, 0.3, 1));
    assert(n == tuple::vec(0, 0, 1));

    n = c.local_normal_at(tuple::point(0.4, 0.4, -1));
    assert(n == tuple::vec(0, 0, -1));

    n = c.local_normal_at(tuple::point(1, 1, 1));
    assert(n == tuple::vec(1, 0, 0));

    n = c.local_normal_at(tuple::point(-1, -1, -1));
    assert(n == tuple::vec(-1, 0, 0));
}