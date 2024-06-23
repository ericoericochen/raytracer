#include <iostream>
#include <vector>
#include "../include/world.h"
#include "../include/shapes/sphere.h"
#include "../include/shapes/shape.h"
#include "../include/shapes/plane.h"
#include "../include/shapes/cylinder.h"
#include "../include/matrix.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/camera.h"
#include "../include/tuple.h"

int main()
{
    Plane floor = Plane();

    Cylinder middle = Cylinder(0, 1);
    middle.transform = matrix::translation(-0.5, 1, 0.5) * matrix::rotation_x(M_PI / 4);
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    World world = World();
    world.light = light::point_light(tuple::point(-10, 10, -10), Color(1, 1, 1));

    world.objects = std::vector<Shape *>{
        &floor,
        &middle};

    // Camera camera = Camera(100, 50, M_PI / 3);
    Camera camera = Camera(500, 250, M_PI / 3);
    auto from = tuple::point(0, 1.5, -5);
    auto to = tuple::point(0, 1, 0);
    auto up = tuple::vec(0, 1, 0);
    camera.transform = matrix::view_transform(from,
                                              to,
                                              up);

    auto image = world.render(camera);
    std::cout << image.to_ppm() << std::endl;
}