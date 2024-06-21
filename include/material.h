#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "patterns/stripe.h"

class Material
{
public:
    Color color;
    double ambient, diffuse, specular, shininess;
    Stripe *pattern = nullptr;

    Material();
};

#endif