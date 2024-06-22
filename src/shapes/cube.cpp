#include "../../include/shapes/cube.h"
#include "../../include/utils.h"
#include <vector>

Cube::Cube() {}

std::vector<double> check_axis(double o, double d)
{
    double tmin_numerator = -1 - o;
    double tmax_numerator = 1 - o;

    double tmin, tmax;

    if (std::abs(d) >= EPSILON)
    {
        tmin = tmin_numerator / d;
        tmax = tmax_numerator / d;
    }
    else
    {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax)
    {
        std::swap(tmin, tmax);
    }

    return {tmin, tmax};
}

std::vector<Intersection> Cube::local_intersects(Ray &local_ray)
{
    double xtmin, xtmax, ytmin, ytmax, ztmin, ztmax;

    auto xresult = check_axis(local_ray.origin.x, local_ray.direction.x);
    xtmin = xresult[0];
    xtmax = xresult[1];

    auto yresult = check_axis(local_ray.origin.y, local_ray.direction.y);
    ytmin = yresult[0];
    ytmax = yresult[1];

    auto zresult = check_axis(local_ray.origin.z, local_ray.direction.z);
    ztmin = zresult[0];
    ztmax = zresult[1];

    double tmin = std::max({xtmin, ytmin, ztmin});
    double tmax = std::min({xtmax, ytmax, ztmax});

    if (tmin > tmax)
    {
        return {};
    }

    return {Intersection(this, tmin), Intersection(this, tmax)};
}

Tuple Cube::local_normal_at(const Tuple &local_point) const
{
    double maxc = std::max(abs(local_point.x), std::max(abs(local_point.y), abs(local_point.z)));

    if (maxc == abs(local_point.x))
    {
        return tuple::vec(local_point.x, 0, 0);
    }
    else if (maxc == abs(local_point.y))
    {
        return tuple::vec(0, local_point.y, 0);
    }
    else
    {
        return tuple::vec(0, 0, local_point.z);
    }
}