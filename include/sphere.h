#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "tuple.h"
#include "ray.h"
#include "intersection.h"
#include "matrix.h"
#include "material.h"

class Sphere
{
public:
    Material material = Material();
    Matrix transform = matrix::eye(4);
    Sphere();
    Sphere(Material material);
    void set_transform(const Matrix &matrix);
    std::vector<Intersection> intersects(Ray &ray);
    Tuple normal_at(const Tuple &world_point) const;
};

#endif