#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "../matrix.h"
#include "../material.h"
#include "../transforms.h"
#include "../intersection.h"
#include "../ray.h"

class Shape
{
public:
    Matrix transform = transforms::eye();
    Material material = Material();
    Ray saved_ray = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 0));

    Shape();

    std::vector<Intersection> intersects(Ray &ray);
    virtual std::vector<Intersection> local_intersects(Ray &local_ray);

    Tuple normal_at(const Tuple &world_point) const;
    Tuple local_normal_at(const Tuple &local_point) const;
};

#endif