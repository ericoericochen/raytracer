
#include "../../include/patterns/pattern.h"
#include "../../include/color.h"

Pattern::Pattern() {}

Pattern::~Pattern()
{
    // delete &this->transform;
}

Color Pattern::pattern_at(const Tuple &point) const
{
    return Color(point.x, point.y, point.z);
}