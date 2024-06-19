#include <iostream>
#include <vector>
#include "../include/world.h"
#include "../include/shapes/sphere.h"
#include "../include/shapes/shape.h"
#include "../include/matrix.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/camera.h"
#include "../include/tuple.h"

int main()
{
    Sphere floor = Sphere();
    floor.transform = matrix::scaling(10, 0.01, 10);

    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere left_wall = Sphere();
    left_wall.transform = matrix::translation(0, 0, 5) * matrix::rotation_y(-M_PI / 4) *
                          matrix::rotation_x(-M_PI / 2) * matrix::scaling(10, 0.01, 10);
    left_wall.material = floor.material;

    Sphere right_wall = Sphere();
    right_wall.transform = matrix::translation(0, 0, 5) *
                           matrix::rotation_y(M_PI / 4) * matrix::rotation_x(M_PI / 2) *
                           matrix::scaling(10, 0.01, 10);
    right_wall.material = floor.material;

    Sphere middle = Sphere();
    middle.transform = matrix::translation(-0.5, 1, 0.5);
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right = Sphere();
    right.transform = matrix::translation(1.5, 0.5, -0.5) * matrix::scaling(0.5, 0.5, 0.5);
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left = Sphere();
    left.transform = matrix::translation(-1.5, 0.33, -0.75) * matrix::scaling(0.33, 0.33, 0.33);
    left.material.color = Color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    World world = World();
    world.light = light::point_light(tuple::point(-10, 10, -10), Color(1, 1, 1));

    world.objects = std::vector<Shape *>{
        &floor,
        &right_wall,
        &left_wall,
        &middle,
        &left,
        &right};

    Camera camera = Camera(100, 50, M_PI / 3);
    // Camera camera = Camera(500, 250, M_PI / 3);
    auto from = tuple::point(0, 1.5, -5);
    auto to = tuple::point(0, 1, 0);
    auto up = tuple::vec(0, 1, 0);
    camera.transform = matrix::view_transform(from,
                                              to,
                                              up);

    auto image = world.render(camera);
    std::cout << image.to_ppm() << std::endl;
}