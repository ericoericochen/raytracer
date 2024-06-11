#ifndef SPHERE_H
#define SPHERE_H

#include "tuple.h"
#include "ray.h"
#include "intersection.h"

class Sphere
{
public:
    Tuple origin = tuple::point(0, 0, 0);
    double radius = 1.0;

    Sphere();
    Sphere(Tuple origin, double radius);

    Intersection intersects(Ray &ray);
};

#endif