#include "tuple.cpp"

class Color : Tuple
{
public:
    Color() : Tuple() {}
    Color(double r, double g, double b) : Tuple(r, g, b, 0) {}
};