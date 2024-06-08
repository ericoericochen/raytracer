#include "tuple.cpp"

class Color : public Tuple
{
public:
    Color() : Tuple() {}
    Color(double r, double g, double b) : Tuple(r, g, b, 0) {}
    double r() { return this->x(); }
    double g() { return this->y(); }
    double b() { return this->z(); }
};