#include <cmath>
#include <iostream>

#include "../../include/patterns/ring.h"
#include "../../include/color.h"
#include "../../include/tuple.h"

Ring::Ring(Color a, Color b) : a(a), b(b) {}

Color Ring::pattern_at(const Tuple &point) const
{
    return (int)floor(sqrt(point.x * point.x + point.z * point.z)) % 2 == 0 ? this->a : this->b;
}