#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Sphere;

class Intersection
{

public:
    Sphere *object;
    int t;

public:
    Intersection(Sphere *object, int t);
};

#endif
