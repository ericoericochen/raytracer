#include <cmath>
#include <iostream>

#include "../../include/patterns/checker.h"
#include "../../include/color.h"
#include "../../include/tuple.h"

Checker::Checker(Color a, Color b) : a(a), b(b) {}

Color Checker::pattern_at(const Tuple &point) const
{
    return (int)(floor(point.x) + floor(point.y) + floor(point.z)) % 2 == 0 ? this->a : this->b;
}