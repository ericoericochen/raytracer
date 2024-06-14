#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "light.h"
#include "tuple.h"
#include "color.h"
#include "sphere.h"
#include "intersection.h"
#include "ray.h"

class World
{
public:
    PointLight light;
    std::vector<Sphere> objects;

    World();

    std::vector<Intersection> intersects(Ray &ray);
};

#endif