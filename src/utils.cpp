#include <cstdlib>

using namespace std;
const double EPSILON = 0.00001;

bool equal(double a, double b)
{
    return abs(a - b) < EPSILON;
}