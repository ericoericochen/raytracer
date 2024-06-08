#include "tuple.h"
#include <cassert>
#include <iostream>

using namespace std;
const double EPSILON = 0.00001;

bool equal(double a, double b)
{
    return abs(a - b) < EPSILON;
}

Tuple::Tuple()
{
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
    e[3] = 0;
}

Tuple::Tuple(double x, double y, double z, double w)
{
    e[0] = x;
    e[1] = y;
    e[2] = z;
    e[3] = w;
}

bool Tuple::is_point() const { return this->w() == 1.0; }
bool Tuple::is_vector() const { return this->w() == 0.0; }