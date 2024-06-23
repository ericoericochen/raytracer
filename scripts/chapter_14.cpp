#include <iostream>
#include <vector>
#include "../include/world.h"
#include "../include/shapes/sphere.h"
#include "../include/shapes/shape.h"
#include "../include/shapes/plane.h"
#include "../include/shapes/group.h"
#include "../include/shapes/cylinder.h"
#include "../include/matrix.h"
#include "../include/color.h"
#include "../include/light.h"
#include "../include/camera.h"
#include "../include/tuple.h"

Shape *hexagon_corner()
{
    auto corner = new Sphere();
    corner->transform = matrix::translation(0, 0, -1) * matrix::scaling(0.25, 0.25, 0.25);
    return corner;
}

Shape *hexagon_edge()
{
    auto edge = new Cylinder();
    edge->min = 0;
    edge->max = 1;
    edge->transform = matrix::translation(0, 0, -1) * matrix::rotation_y(-M_PI / 6) * matrix::rotation_z(-M_PI / 2) * matrix::scaling(0.25, 1, 0.25);
    return edge;
}

Shape *hexagon_side()
{
    auto side = new Group();
    auto corner = hexagon_corner();
    auto edge = hexagon_edge();
    side->add_child(corner);
    side->add_child(edge);
    return side;
}

Shape *hexagon()
{
    auto hex = new Group();
    for (int n = 0; n < 6; n++)
    {
        auto side = hexagon_side();
        side->transform = matrix::rotation_y(n * M_PI / 3);
        hex->add_child(side);
    }
    return hex;
}

int main()
{
    // Plane floor = Plane();
    auto hex = hexagon();
    hex->transform = matrix::translation(0, 1, 0) * matrix::rotation_x(M_PI / 3);

    World world = World();
    world.light = light::point_light(tuple::point(-10, 10, -10), Color(1, 1, 1));

    world.objects = std::vector<Shape *>{
        hex,
        // &floor
    };

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