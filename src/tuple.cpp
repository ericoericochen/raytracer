#include <cassert>
#include <iostream>
#include <cstdlib>
#include "utils.cpp"

class Tuple
{
private:
    double e[4];

public:
    Tuple() : e{0, 0, 0, 0} {}

    Tuple(double x, double y, double z, double w) : e{x, y, z, w} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double w() const { return e[3]; }

    bool is_point() const { return w() == 1.0; }
    bool is_vector() const { return w() == 0.0; }

    double operator[](int i) const { return e[i]; }
    bool operator==(const Tuple &other) const
    {
        return equal(x(), other.x()) && equal(y(), other.y()) && equal(z(), other.z()) && equal(w(), other.w());
    }

    Tuple operator+(const Tuple &other) const
    {
        return Tuple(this->x() + other.x(), this->y() + other.y(), this->z() + other.z(), this->w() + other.w());
    }

    Tuple operator-() const { return Tuple(-x(), -y(), -z(), -w()); }

    Tuple operator-(const Tuple &other) const
    {
        return Tuple(
            x() - other.x(),
            y() - other.y(),
            z() - other.z(),
            w() - other.w());
    }

    Tuple operator*(double scalar) const
    {
        return Tuple(this->x() * scalar, this->y() * scalar, this->z() * scalar, this->w() * scalar);
    }

    // Hadamard product
    Tuple operator*(const Tuple &other) const
    {
        return Tuple(this->x() * other.x(), this->y() * other.y(), this->z() * other.z(), this->w() * other.w());
    }

    Tuple operator/(double scalar) const { return *this * (1 / scalar); }
    double magnitude() { return sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z() + this->w() * this->w()); }
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

        return Tuple(y() * other.z() - z() * other.y(),
                     z() * other.x() - x() * other.z(),
                     x() * other.y() - y() * other.x(), 0.0);
    }
};

namespace primitive
{
    Tuple point(double x, double y, double z) { return Tuple(x, y, z, 1.0); }
    Tuple vec(double x, double y, double z) { return Tuple(x, y, z, 0.0); }
}

Tuple create_tuple(double x, double y, double z, double w) { return Tuple(x, y, z, w); }
Tuple create_point(double x, double y, double z) { return Tuple(x, y, z, 1.0); }
Tuple create_vector(double x, double y, double z) { return Tuple(x, y, z, 0.0); }
