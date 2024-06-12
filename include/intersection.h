#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Sphere;

class Intersection
{

public:
    Sphere *object;
    double t;

public:
    Intersection(Sphere *object, double t);
};

namespace intersection
{
    const Intersection *hit(std::vector<Intersection *> &intersections);
}

#endif