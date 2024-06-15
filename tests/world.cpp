#include <cassert>
#include <iostream>
#include "../include/world.h"
#include "../include/ray.h"
#include "../include/tuple.h"
#include "../include/intersection.h"
#include "../include/prepared_computation.h"
#include "../include/shading.h"
#include "../include/light.h"

int main()
{
    World w = World();
    Ray r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    auto xs = w.intersects(r);

    assert(xs.size() == 4 && xs[0].t == 4.0 && xs[1].t == 4.5 && xs[2].t == 5.5 && xs[3].t == 6);

    // shading
    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    auto i = Intersection(&w.objects[0], 4.0);
    auto comps = prepare_computation(i, r);
    auto c = shade_hit(w, comps);

    assert(c == Color(0.38066, 0.47583, 0.2855));

    // shading inside
    w = World();
    w.light = PointLight(tuple::point(0, 0.25, 0), Color(1, 1, 1));
    r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    i = Intersection(&w.objects[1], 0.5);
    comps = prepare_computation(i, r);
    c = shade_hit(w, comps);

    assert(c == Color(0.90498, 0.90498, 0.90498));

    // color at
    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 1, 0));
    c = w.color_at(r);

    assert(c == Color(0, 0, 0));

    w = World();
    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));
    c = w.color_at(r);

    assert(c == Color(0.38066, 0.47583, 0.2855));

    w = World();
    auto outer = &w.objects[0];
    outer->material.ambient = 1;

    auto inner = &w.objects[1];
    inner->material.ambient = 1;

    r = Ray(tuple::point(0, 0, 0.75), tuple::vec(0, 0, -1));
    c = w.color_at(r);

    assert(c == inner->material.color);
}
