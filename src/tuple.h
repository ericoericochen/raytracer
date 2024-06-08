class Tuple
{
private:
    double e[4];

public:
    Tuple() {}
    Tuple(double x, double y, double z, double w) {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double w() const { return e[3]; }

    bool is_point() const {}
    bool is_vector() const {}

    bool operator==(const Tuple &other) {}
    Tuple operator+(const Tuple &other) {}
    Tuple operator-() {}
    Tuple operator-(const Tuple &other) {}
    Tuple operator*(double scalar) {}
    Tuple operator/(double scalar) {}

    double magnitude() {}
    Tuple normalize() {}
    double dot(const Tuple &other) {}
    Tuple cross(const Tuple &other) {}
};

Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);