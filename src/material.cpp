#include "../include/material.h"
#include "../include/color.h"

Material::Material(Color color, double ambient, double diffuse, double specular, double shininess)
{
    this->color = color;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}