#ifndef PREPARED_COMPUTATION_H
#define PREPARED_COMPUTATION_H

#include <vector>
#include "shapes/shape.h"
#include "tuple.h"
#include "intersection.h"
#include "ray.h"

class PreparedComputation
{
public:
    double t;
    Shape *object;
    Tuple point, eyev, normalv, over_point, reflectv, under_point;
    bool inside;
    double n1, n2;

    PreparedComputation(double t, Shape *object, Tuple point, Tuple eyev, Tuple normalv, bool inside, Tuple over_point = tuple::point(0, 0, 0), Tuple reflectv = tuple::vec(0, 0, 0),
                        double n1 = 1, double n2 = 1, Tuple under_point = tuple::point(0, 0, 0));
};

PreparedComputation prepare_computation(Intersection &intersection, Ray &ray);
PreparedComputation prepare_computation(Intersection &intersection, Ray &ray, std::vector<Intersection> &xs);

#endif