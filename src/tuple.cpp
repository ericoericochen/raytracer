#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace std;
const double EPSILON = 0.00001;

bool equal(double a, double b)
{
    return abs(a - b) < EPSILON;
}

class Tuple
{
private:
    double e[4];

public:
    Tuple()
    {
        e[0] = 0.0;
        e[1] = 0.0;
        e[2] = 0.0;
        e[3] = 0.0;
    }

    Tuple(double x, double y, double z, double w)
    {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        e[3] = w;
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double w() const { return e[3]; }

    bool is_point() const { return w() == 1.0; }
    bool is_vector() const { return w() == 0.0; }

    double operator[](int i) const { return e[i]; }
    bool operator==(const Tuple &other)
    {
        return equal(x(), other.x()) &&
               equal(y(), other.y()) &&
               equal(z(), other.z()) &&
               equal(w(), other.w());
    }

    Tuple operator+(const Tuple &other)
    {
        return Tuple(x() + other.x(),
                     y() + other.y(),
                     z() + other.z(),
                     w() + other.w());
    }

    Tuple operator-() { return Tuple(-x(), -y(), -z(), -w()); }

    Tuple operator-(const Tuple &other)
    {
        return Tuple(
            x() - other.x(),
            y() - other.y(),
            z() - other.z(),
            w() - other.w());
    }

    Tuple operator*(double scalar)
    {
        return Tuple(
            x() * scalar,
            y() * scalar,
            z() * scalar,
            w() * scalar);
    }

    Tuple operator/(double scalar) { return *this * (1 / scalar); }

    double magnitude()
    {
        return sqrt(
            x() * x() + y() * y() + z() * z() + w() * w());
    }

    Tuple normalize() { return *this / magnitude(); }

    double dot(const Tuple &other)
    {
        double result = 0;
        for (int i = 0; i < 4; i++)
        {
            result += (*this)[i] * other[i];
        }

        return result;
    }

    Tuple cross(const Tuple &other)
    {
        assert(is_vector() && other.is_vector());

        return Tuple(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x(), 0.0);
    }
};

Tuple create_tuple(double x, double y, double z, double w) { return Tuple(x, y, z, w); }
Tuple create_point(double x, double y, double z) { return Tuple(x, y, z, 1.0); }
Tuple create_vector(double x, double y, double z) { return Tuple(x, y, z, 0.0); }
