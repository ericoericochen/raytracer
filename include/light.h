
#ifndef LIGHT_H
#define LIGHT_H

#include "tuple.h"
#include "color.h"

class PointLight
{
public:
    Tuple position;
    Color intensity;
    PointLight();
    PointLight(Tuple position, Color intensity);
};

namespace light
{
    PointLight point_light(Tuple position, Color intensity);
}

#endif