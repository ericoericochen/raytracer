
#include <cassert>
#include "../../include/shapes/group.h"
#include "../../include/shapes/sphere.h"
#include "../../include/transforms.h"
#include "../../include/tuple.h"

int main()
{
    //  Intersecting a ray with an empty group
    Group g = Group();
    Ray r = Ray(tuple::point(0, 0, 0), tuple::vec(0, 0, 1));
    auto xs = g.local_intersects(r);

    assert(xs.size() == 0);

    // Intersecting a ray with a non-empty group
    Sphere s1 = Sphere();
    Sphere s2 = Sphere();
    Sphere s3 = Sphere();

    s2.transform = transforms::translation(0, 0, -3);
    s3.transform = transforms::translation(5, 0, 0);

    g.add_child(&s1);
    g.add_child(&s2);
    g.add_child(&s3);

    r = Ray(tuple::point(0, 0, -5), tuple::vec(0, 0, 1));

    xs = g.local_intersects(r);

    assert(xs.size() == 4);
    assert(xs[0].object == &s2);
    assert(xs[1].object == &s2);
    assert(xs[2].object == &s1);
    assert(xs[3].object == &s1);

    // Intersecting a transformed group
    g = Group();
    g.transform = transforms::scaling(2, 2, 2);
    Sphere s = Sphere();
    s.transform = transforms::translation(5, 0, 0);
    g.add_child(&s);

    r = Ray(tuple::point(10, 0, -10), tuple::vec(0, 0, 1));
    xs = g.intersects(r);

    assert(xs.size() == 2);

    // Converting a point from world to object space
    g = Group();
    g.transform = transforms::rotation_y(M_PI / 2);
    Group g2 = Group();
    g2.transform = transforms::scaling(2, 2, 2);
    g.add_child(&g2);
    s = Sphere();
    s.transform = transforms::translation(5, 0, 0);
    g2.add_child(&s);

    auto p = s.world_to_object(tuple::point(-2, 0, -10));
    assert(p == tuple::point(0, 0, -1));

    // Converting a normal from object to world space
    auto g1 = Group();
    g1.transform = transforms::rotation_y(M_PI / 2);
    g2 = Group();
    g2.transform = transforms::scaling(1, 2, 3);
    g1.add_child(&g2);
    s = Sphere();
    s.transform = transforms::translation(5, 0, 0);
    g2.add_child(&s);
    auto n = s.normal_to_world(tuple::vec(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    assert(n == tuple::vec(0.2857, 0.4286, -0.8571));

    // Finding the normal on a child object
    g1 = Group();
    g1.transform = transforms::rotation_y(M_PI / 2);
    g2 = Group();
    g2.transform = transforms::scaling(1, 2, 3);
    g1.add_child(&g2);
    s = Sphere();
    s.transform = transforms::translation(5, 0, 0);
    g2.add_child(&s);
    n = s.normal_at(tuple::point(1.7321, 1.1547, -5.5774));
    assert(n == tuple::vec(0.2857, 0.4286, -0.8571));
}