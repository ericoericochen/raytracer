#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Sphere;

class Intersection
{

private:
    Sphere *m_object;
    std::vector<double> m_hits;

public:
    Intersection(Sphere *object, std::vector<double> hits);
    int count() const;
    Sphere *object() const;
    double operator[](int i) const;
};

#endif
