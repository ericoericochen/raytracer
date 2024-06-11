#include <cassert>
#include "../include/sphere.h"
#include "../include/ray.h"
#include "../include/tuple.h"

int main()
{
    auto origin = tuple::point(0, 0, -5);
    auto direction = tuple::vec(0, 0, 1);
    auto r = Ray(origin, direction);
    auto s = Sphere();

    auto xs = sphere::intersects(s, r);

    assert(xs.size() == 2 && xs[0] == 4.0 && xs[1] == 6.0);
}