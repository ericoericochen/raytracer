#include <vector>
#include "../include/intersection.h"
#include "../include/sphere.h"

Intersection::Intersection(Sphere *object, std::vector<double> hits) : m_object(object), m_hits(hits) {}
int Intersection::count() const { return m_hits.size(); }
Sphere *Intersection::object() const { return m_object; }
double Intersection::operator[](int i) const { return m_hits[i]; }
