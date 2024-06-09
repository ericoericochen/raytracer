#include <cassert>
#include "tuple.cpp"
#include "intersect.cpp"
#include "ray.cpp"

class Sphere
{
public:
    Tuple origin = primitive::point(0, 0, 0);
    double radius = 1.0;

    Sphere() {}
    Sphere(Tuple origin, double radius)
    {
        assert(origin.is_point());
        this->origin = origin;
        this->radius = radius;
    }

    Intersection intersects(Ray &ray)
    {
    }
};