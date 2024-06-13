#include <string>
#include "../include/tuple.h"
#include "../include/color.h"

Color::Color() : Tuple() {}
Color::Color(double r, double g, double b) : Tuple(r, g, b, 0) {}

const double &Color::r() const { return this->x; }
const double &Color::g() const { return this->y; }
const double &Color::b() const { return this->z; }

Color Color::operator*(const Color &other) const
{
    return Color(this->r() * other.r(), this->g() * other.g(), this->b() * other.b());
}

Color Color::operator*(const double scalar) const
{
    return Color(this->r() * scalar, this->g() * scalar, this->b() * scalar);
}

Color Color::operator+(const Color &other) const
{
    return Color(this->r() + other.r(), this->g() + other.g(), this->b() + other.b());
}

std::string Color::to_string() const
{
    return "Color(" + std::to_string(this->r()) + ", " + std::to_string(this->g()) + ", " + std::to_string(this->b()) + ")";
}