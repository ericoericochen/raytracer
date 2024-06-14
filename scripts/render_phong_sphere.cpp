#include <iostream>
#include "../include/sphere.h"
#include "../include/ray.h"
#include "../include/canvas.h"
#include "../include/tuple.h"
#include "../include/material.h"
#include "../include/light.h"

int main()
{
    int width = 100, height = 100;
    Canvas canvas = Canvas(width, height);
    double wall_size = 7.0;
    double wall_z = 10.0;
    Tuple ray_origin = tuple::point(0, 0, -5);
    double pixel_size = wall_size / width;

    // sphere
    Sphere sphere = Sphere();
    sphere.material.color = Color(1, 0.2, 1);

    // lighting
    auto light_position = tuple::point(-10, 10, -10);
    auto light_color = Color(1, 1, 1);
    auto light = light::point_light(light_position, light_color);
    // sphere.transform = matrix::scaling(1, 0.5, 1);
    // sphere.transform = matrix::rotation_z(M_PI / 4) * matrix::scaling(1, 0.5, 1);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // translate canvas coordinates to world coordinates
            double world_x = -wall_size / 2 + pixel_size * x + pixel_size / 2;
            double world_y = wall_size / 2 - pixel_size * y + pixel_size / 2;

            // cast ray into the scene
            Tuple pos = tuple::point(world_x, world_y, wall_z);
            Tuple direction = (pos - ray_origin).normalize();
            Ray ray = Ray(ray_origin, direction);

            // check intersection
            auto intersections = sphere.intersects(ray);
            auto hit = intersection::hit(intersections);

            // color pixel if hit
            if (hit.has_value())
            {
                auto hit_object = hit.value();
                auto object = hit_object->object;
                auto point = ray.position_at(hit_object->t);
                Tuple normal = object->normal_at(point);
                Color color = lighting(object->material, light, point, -ray.direction, normal);
                canvas.write_pixel(x, y, color);
            }
        }
    }

    std::cout << canvas.to_ppm() << std::endl;
}
