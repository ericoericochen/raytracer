#include <iostream>
#include <vector>
#include "../include/world.h"
#include "../include/shapes/sphere.h"
#include "../include/shapes/shape.h"
#include "../include/patterns/checker.h"
#include "../include/shapes/plane.h"
#include "../include/matrix.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/camera.h"
#include "../include/tuple.h"

int main()
{
    auto w = World();
    auto floor = Plane();
    floor.transform = transforms::translation(0, -1, 0);
    floor.material.pattern = new Checker(Color(1, 1, 1), Color(0, 0, 0));
    // floor.material.transparency = 0.5;
    // floor.material.refractive_index = 1.5;

    auto ball = Sphere();
    ball.material.color = Color(0, 0, 0);
    ball.material.ambient = 0.0;
    ball.material.transparency = 0.8;
    ball.material.refractive_index = 1.5;
    ball.material.reflective = 0.7;
    ball.transform = matrix::translation(-0.5, 1, 0.5);
    w.objects = {&floor, &ball};

    // Camera camera = Camera(100, 50, M_PI / 3);
    Camera camera = Camera(500, 250, M_PI / 3);
    auto from = tuple::point(0, 1.5, -5);
    auto to = tuple::point(0, 1, 0);
    auto up = tuple::vec(0, 1, 0);
    camera.transform = matrix::view_transform(from,
                                              to,
                                              up);

    auto image = w.render(camera);
    std::cout << image.to_ppm() << std::endl;
}