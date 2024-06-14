#ifndef PREPARED_COMPUTATION_H
#define PREPARED_COMPUTATION_H

#include "sphere.h"
#include "tuple.h"
#include "intersection.h"
#include "ray.h"

class PreparedComputation
{
public:
    double t;
    Sphere *object;
    Tuple point, eyev, normalv;
    bool inside;

    PreparedComputation(double t, Sphere *object, Tuple point, Tuple eyev, Tuple normalv, bool inside);
};

PreparedComputation prepare_computation(Intersection &intersection, Ray &ray);

#endif