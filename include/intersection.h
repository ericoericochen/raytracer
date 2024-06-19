#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Shape;

class Intersection
{

public:
    Shape *object;
    double t;

public:
    Intersection(Shape *object, double t);
};

namespace intersection
{
    std::optional<Intersection *> hit(std::vector<Intersection> &intersections);
}

#endif
