#include <cmath>
#include <cassert>
#include "../include/tuple.h"
#include "../include/utils.h"

Tuple::Tuple() : x(0), y(0), z(0), w(0) {}
Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

bool Tuple::is_point() const { return this->w == 1; }
bool Tuple::is_vector() const { return this->w == 0.0; }

double Tuple::operator[](int i) const
{
    double e[4] = {x, y, z, w};
    return e[i];
}

bool Tuple::operator==(const Tuple &other) const
{
    return equal(this->x, other.x) && equal(this->y, other.y) && equal(this->z, other.z) && equal(this->w, other.w);
}

Tuple Tuple::operator+(const Tuple &other) const
{
    return Tuple(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

Tuple Tuple::operator-() const { return Tuple(-this->x, -this->y, -this->z, -this->w); }

Tuple Tuple::operator-(const Tuple &other) const
{
    return Tuple(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

Tuple Tuple::operator*(double scalar) const
{
    return Tuple(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}

// Hadamard product
Tuple Tuple::operator*(const Tuple &other) const
{
    return Tuple(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

Tuple Tuple::operator/(double scalar) const { return *this * (1 / scalar); }
double Tuple::magnitude() const { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w); }
Tuple Tuple::normalize() const { return *this / magnitude(); }

double Tuple::dot(const Tuple &other) const
{
    double result = 0;
    for (int i = 0; i < 4; i++)
    {
        result += (*this)[i] * other[i];
    }

    return result;
}

Tuple Tuple::cross(const Tuple &other) const
{
    assert(is_vector() && other.is_vector());

    return Tuple(this->y * other.z - this->z * other.y,
                 this->z * other.x - this->x * other.z,
                 this->x * other.y - this->y * other.x, 0.0);
}

namespace tuple
{
    Tuple tuple() { return tuple(0, 0, 0, 0); }
    Tuple tuple(double x, double y, double z, double w) { return Tuple(x, y, z, w); }
    Tuple point() { return point(0, 0, 0); }
    Tuple point(double x, double y, double z) { return Tuple(x, y, z, 1.0); }
    Tuple vec() { return vec(0, 0, 0); }
    Tuple vec(double x, double y, double z) { return Tuple(x, y, z, 0.0); }
}