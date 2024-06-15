#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material
{
public:
    Color color;
    double ambient, diffuse, specular, shininess;

    Material();
    // Material(Color color, double ambient, double diffuse, double specular, double shininess);
};

#endif