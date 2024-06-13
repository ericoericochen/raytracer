
#ifndef LIGHT_H
#define LIGHT_H

#include "tuple.h"
#include "color.h"
#include "material.h"

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

Color lighting(Material material, PointLight light, Tuple position, Tuple eye, Tuple normal);

#endif