#include "../include/light.h"
#include "../include/color.h"

PointLight::PointLight()
{
    this->position = tuple::point();
    this->intensity = Color(1, 1, 1);
}

PointLight::PointLight(Tuple position, Color intensity)
{
    this->position = position;
    this->intensity = intensity;
}

namespace light
{
    PointLight point_light(Tuple position, Color intensity) { return PointLight(position, intensity); }
}