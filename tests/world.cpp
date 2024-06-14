#include <cassert>
#include <iostream>
#include "../include/world.h"
#include "../include/ray.h"
#include "../include/tuple.h"

int main()
{
    World w = World();
    Ray r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    auto xs = w.intersects(r);

    std::cout << xs.size() << std::endl;

    assert(xs.size() == 4 && xs[0].t == 4.0 && xs[1].t == 4.5 && xs[2].t == 5.5 && xs[3].t == 6);
}