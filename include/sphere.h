#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "tuple.h"
#include "ray.h"
#include "intersection.h"
#include "matrix.h"

class Sphere
{
public:
    Matrix transform = matrix::eye(4);
    Sphere();
    void set_transform(const Matrix &matrix);
    std::vector<Intersection> intersects(Ray &ray);
};

namespace sphere
{
    std::vector<Intersection> intersects(Sphere &sphere, Ray &ray);
}

#endif