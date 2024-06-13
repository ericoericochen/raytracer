#include <cmath>
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

Color lighting(Material material, PointLight light, Tuple point, Tuple eyev, Tuple normalv)
{
    // combine surface color with light's color/intensity
    Color effective_color = material.color * light.intensity;

    // direction to the light source
    auto lightv = (light.position - point).normalize();

    // compute ambient contribution
    Color ambient = effective_color * material.ambient;

    // light_dot_normal represents the cosine of the angle between the
    // light vector and the normal vector. A negative number means the
    // light is on the other side of the surface.
    double light_dot_normal = lightv.dot(normalv);

    Color diffuse, specular;

    if (light_dot_normal < 0)
    {
        diffuse = Color(0, 0, 0);
        specular = Color(0, 0, 0);
    }
    else
    {
        // compute the diffuse contribution
        diffuse = effective_color * material.diffuse * light_dot_normal;

        // reflect_dot_eye represents the cosine of the angle between the
        // reflection vector and the eye vector. A negative number means the
        // light reflects away from the eye.
        Tuple reflectv = tuple::reflect(-lightv, normalv);
        double reflect_dot_eye = reflectv.dot(eyev);

        if (reflect_dot_eye <= 0)
        {
            specular = Color(0, 0, 0);
        }
        else
        {
            // compute the specular contribution
            double factor = std::pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}