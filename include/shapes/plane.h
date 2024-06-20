#ifndef PLANE_H
#define PLANE_H

#include "./shape.h"
#include "../ray.h"
#include "../intersection.h"
#include "../tuple.h"

class Plane : public Shape
{
public:
    Plane();

    std::vector<Intersection> local_intersects(Ray &local_ray) override;
    Tuple local_normal_at(const Tuple &local_point) const override;
};

#endif