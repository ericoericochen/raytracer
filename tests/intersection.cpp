#include <cassert>
#include "../include/intersection.h"
#include "../include/sphere.h"

int main()
{
    Sphere s = Sphere();
    Intersection i = Intersection(&s, 3);

    assert(i.object == &s && i.t == 3);
}