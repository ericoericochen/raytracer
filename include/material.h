#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material
{
public:
    Color color;
    double ambient, diffuse, specular, shininess;

    Material(Color color = Color(1, 1, 1), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200.0);
};

#endif