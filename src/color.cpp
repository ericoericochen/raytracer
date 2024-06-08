#include "tuple.cpp"
#include <string>
#include <iostream>

class Color : public Tuple
{
public:
    Color() : Tuple() {}
    Color(double r, double g, double b) : Tuple(r, g, b, 0) {}
    double r() const { return this->x(); }
    double g() const { return this->y(); }
    double b() const { return this->z(); }

    string to_string() const
    {
        return "Color(" + std::to_string(this->r()) + ", " + std::to_string(this->g()) + ", " + std::to_string(this->b()) + ")";
    }
};