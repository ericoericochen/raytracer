#include "utils.h"
#include <cmath>

bool equal(double a, double b)
{
    return std::abs(a - b) < EPSILON;
}
