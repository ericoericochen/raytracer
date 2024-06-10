#include <vector>
#include "sphere.cpp"

using namespace std;

class Intersection
{

private:
    Sphere &m_object;
    vector<double> m_hits;

public:
    Intersection(Sphere &object, vector<double> hits) : m_object(object), m_hits(hits) {}
    int count() const { return m_hits.size(); }
    Sphere &object() const { return m_object; }

    double operator[](int i) const { return m_hits[i]; }
};
