#include <cassert>
#include <iostream>
#include "../src/canvas.cpp"

using namespace std;

int main()
{
    Canvas c = Canvas(10, 20);

    assert(c.width() == 10 && c.height() == 20);

    for (const vector<Color> &row : c.pixels())
    {
        for (const Color &color : row)
        {
            // assert(color == Color(0, 0, 0));
            cout << color.to_string() << endl;
        }
    }
}