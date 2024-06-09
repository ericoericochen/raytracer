#include "../src/ray.cpp"
#include "../src/sphere.cpp"

int main()
{
    Tuple origin = primitive::point(1, 2, 3);
    Tuple direction = primitive::vec(4, 5, 6);
    Ray r = Ray(origin, direction);

    assert(r.origin == origin && r.direction == direction);

    // position at
    r = Ray(primitive::point(2, 3, 4), primitive::vec(1, 0, 0));
    assert(r.position_at(0) == primitive::point(2, 3, 4));
    assert(r.position_at(1) == primitive::point(3, 3, 4));
    assert(r.position_at(-1) == primitive::point(1, 3, 4));
    assert(r.position_at(2.5) == primitive::point(4.5, 3, 4));

    // ray sphere intersection
    Sphere s;

    origin = primitive::point(0, 0, -5);
    direction = primitive::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    Intersection intersection = s.intersects(r);
    assert(intersection.count() == 2 && intersection[0] == 4.0 && intersection[1] == 6.0);

    origin = primitive::point(0, 1, -5);
    direction = primitive::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    Intersection intersection = s.intersects(r);
    assert(intersection.count() == 2 && intersection[0] == 5.0 && intersection[1] == 5.0);

    origin = primitive::point(0, 2, -5);
    direction = primitive::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    Intersection intersection = s.intersects(r);
    assert(intersection.count() == 0);

    origin = primitive::point(0, 0, 0);
    direction = primitive::vec(0, 0, 1);
    r = Ray(origin, direction);
    s = Sphere();
    Intersection intersection = s.intersects(r);
    assert(intersection.count() == 2 && intersection[0] == -1.0 && intersection[1] == 1.0);
}