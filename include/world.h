#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "light.h"
#include "tuple.h"
#include "color.h"
#include "shapes/shape.h"
#include "intersection.h"
#include "ray.h"
#include "prepared_computation.h"
#include "camera.h"
#include "canvas.h"

class World
{
public:
    PointLight light;
    std::vector<Shape *> objects;

    World();

    std::vector<Intersection> intersects(Ray &ray);
    Color shade_hit(PreparedComputation &comps);
    Color color_at(Ray &ray);
    Canvas render(Camera &camera);
    bool is_shadowed(Tuple &point);
};

#endif