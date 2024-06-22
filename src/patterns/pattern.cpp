
#include "../../include/patterns/pattern.h"
#include "../../include/color.h"

Pattern::Pattern() {}

Color Pattern::pattern_at(const Tuple &point) const
{
    return Color(point.x, point.y, point.z);
}