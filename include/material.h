#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "patterns/pattern.h"

class Material
{
public:
    Color color;
    double ambient, diffuse, specular, shininess;
    Pattern *pattern = nullptr;

    Material();
};

#endif