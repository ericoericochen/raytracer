#include "../src/color.cpp"
#include <cassert>

int main()
{
    Color c1, c2;
    c1 = Color(0.9, 0.6, 0.75);
    c2 = Color(0.7, 0.1, 0.25);

    // adding colors
    assert(c1 + c2 == Color(1.6, 0.7, 1.0));

    // subtracting colors
    assert(c1 - c2 == Color(0.2, 0.5, 0.5));

    // multiplying a color by a scalar
    c1 = Color(0.2, 0.3, 0.4);
    assert(c1 * 2 == Color(0.4, 0.6, 0.8));

    // multiplying colors
    c1 = Color(1, 0.2, 0.4);
    c2 = Color(0.9, 1, 0.1);
    assert(c1 * c2 == Color(0.9, 0.2, 0.04));
}