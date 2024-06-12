#include <vector>
#include <iostream>
#include "../include/intersection.h"
#include "../include/sphere.h"

Intersection::Intersection(Sphere *object, double t) : object(object), t(t) {}

namespace intersection
{
    const Intersection *hit(std::vector<Intersection *> &intersections)
    {
        double t = std::numeric_limits<double>::infinity();
        const Intersection *hit = nullptr;

        for (const auto i : intersections)
        {
            // std::cout << &i << std::endl;
            auto it = i->t;
            if (i->t >= 0 && i->t < t)
            {
                t = i->t;
                hit = i;
            }
        }

        return hit;
    }
}
