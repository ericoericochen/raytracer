#include <cassert>
#include <vector>
#include <iostream>
#include "../include/intersection.h"
#include "../include/sphere.h"

using namespace std;

int main()
{
    Sphere s = Sphere();
    Intersection i = Intersection(&s, 3);

    assert(i.object == &s && i.t == 3);

    s = Sphere();
    auto i1 = Intersection(&s, 1);
    auto i2 = Intersection(&s, 2);
    std::vector<Intersection *> xs = {&i1, &i2};
    auto i_ = intersection::hit(xs);

    assert(i_ == &i1);

    s = Sphere();
    i1 = Intersection(&s, -1);
    i2 = Intersection(&s, 1);
    xs = {&i1, &i2};
    i_ = intersection::hit(xs);

    assert(i_ == &i2);

    s = Sphere();
    i1 = Intersection(&s, -1);
    i2 = Intersection(&s, -2);
    xs = {&i1, &i2};
    i_ = intersection::hit(xs);

    assert(i_ == nullptr);

    s = Sphere();
    i1 = Intersection(&s, 5);
    i2 = Intersection(&s, 7);
    auto i3 = Intersection(&s, -3);
    auto i4 = Intersection(&s, 2);
    xs = {&i1, &i2, &i3, &i4};
    i_ = intersection::hit(xs);

    assert(i_ == &i4);
}