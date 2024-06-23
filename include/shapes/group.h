#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "./shape.h"
#include "../ray.h"
#include "../intersection.h"
#include "../tuple.h"

class Group : public Shape
{
public:
    std::vector<Shape *> children = {};
    Group();

    std::vector<Intersection> local_intersects(Ray &local_ray) override;
    Tuple local_normal_at(const Tuple &local_point) const override;
    void add_child(Shape *child);
};

#endif