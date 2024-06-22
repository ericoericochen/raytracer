#include <cmath>
#include "../../include/patterns/gradient.h"
#include "../../include/color.h"

Gradient::Gradient(Color a, Color b) : a(a), b(b) {}

Color Gradient::pattern_at(const Tuple &point) const
{
    auto distance = this->b - this->a;
    auto fraction = point.x - floor(point.x);

    return this->a + distance * fraction;
}