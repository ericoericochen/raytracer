#ifndef CUBE_H
#define CUBE_H

#include "./shape.h"
#include "../ray.h"
#include "../intersection.h"
#include "../tuple.h"

class Cube : public Shape
{
    // private:
    //     double[] check_axis(double ray_origin, double ray_direction);

public:
    Cube();

    std::vector<Intersection> local_intersects(Ray &local_ray) override;
    Tuple local_normal_at(const Tuple &local_point) const override;
};

#endif