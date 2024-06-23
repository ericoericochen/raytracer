#ifndef CYLINDER_H
#define CYLINDER_H

#include "./shape.h"
#include "../ray.h"
#include "../intersection.h"
#include "../tuple.h"

class Cylinder : public Shape
{
public:
    double min = -INFINITY;
    double max = INFINITY;
    bool closed = false;
    Cylinder();
    Cylinder(double min, double max, bool closed = false);

    std::vector<Intersection> local_intersects(Ray &local_ray) override;
    Tuple local_normal_at(const Tuple &local_point) const override;
};

#endif