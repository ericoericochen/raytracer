#include <cassert>
#include "../include/material.h"
#include "../include/color.h"

int main()
{
    Material m = Material();
    assert(m.ambient == 0.1 && m.diffuse == 0.9 && m.specular == 0.9 && m.shininess == 200.0);

    Material m2 = Material(Color(1, 1, 1), 0.2, 0.3, 0.4, 0.5);
    assert(m2.ambient == 0.2 && m2.diffuse == 0.3 && m2.specular == 0.4 && m2.shininess == 0.5);
}