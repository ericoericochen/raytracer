#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "sphere.h"

using namespace std;

class Intersection
{

private:
    Sphere &m_object;
    vector<double> m_hits;

public:
    Intersection(Sphere &object, vector<double> hits);
    int count() const;
    Sphere &object() const;
    double operator[](int i) const;
};

#endif
