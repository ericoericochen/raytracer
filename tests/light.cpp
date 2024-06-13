#include <cassert>
#include "../include/light.h"
#include "../include/color.h"

int main()
{
    Color intensity = Color(1, 1, 1);
    Tuple position = tuple::point(0, 0, 0);
    auto light = light::point_light(position, intensity);

    assert(light.position == tuple::point(0, 0, 0) && light.intensity == Color(1, 1, 1));
}