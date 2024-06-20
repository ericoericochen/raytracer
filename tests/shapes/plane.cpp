#include <cassert>
#include "../../include/shapes/plane.h"
#include "../../include/tuple.h"
#include "../../include/ray.h"

int main() {
    Plane p = Plane();

    auto n1 = p.local_normal_at(tuple::point(0, 0, 0));
    auto n2 = p.local_normal_at(tuple::point(10, 0, -10));
    auto n3 = p.local_normal_at(tuple::point(-5, 0, 150));

    assert(n1 == tuple::vec(0, 1, 0));   
    assert(n2 == tuple::vec(0, 1, 0));
    assert(n3 == tuple::vec(0, 1, 0));

    // Intersect with a ray parallel to the plane
    Ray r = Ray(tuple::point(0, 10, 0), tuple::vec(0, 0, 1));
    auto xs = p.local_intersects(r);

    assert(xs.size() == 0);

    // Intersect with a ray coplanar to the plane
    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    xs = p.local_intersects(r);

    assert(xs.size() == 0);

    // A ray intersecting a plane from above
    r = Ray(tuple::point(0, 1, 0), tuple::vec(0, -1, 0));
    xs = p.local_intersects(r);

    assert(xs.size() == 1);
    assert(xs[0].t == 1);
    assert(xs[0].object == &p);

    // A ray intersecting a plane from below
    r = Ray(tuple::point(0, -1, 0), tuple::vec(0, 1, 0));
    xs = p.local_intersects(r);

    assert(xs.size() == 1);
    assert(xs[0].t == 1);
    assert(xs[0].object == &p);


}