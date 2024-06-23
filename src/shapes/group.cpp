#include <vector>
#include <algorithm>
#include "../../include/shapes/group.h"

Group::Group() {}

std::vector<Intersection> Group::local_intersects(Ray &local_ray) {
    std::vector<Intersection> xs;

    for (auto object: this->children) {
        auto child_xs = object->intersects(local_ray);
        xs.insert(xs.end(), child_xs.begin(), child_xs.end());
    }

    // sort by t
    std::sort(xs.begin(), xs.end(), [](Intersection a, Intersection b) {
        return a.t < b.t;
    });

    return xs;
}

Tuple Group::local_normal_at(const Tuple &local_point) const  {}

void Group::add_child(Shape *child) {
    this->children.push_back(child);
    child->parent = this;
}