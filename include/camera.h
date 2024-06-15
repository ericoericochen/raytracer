#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"
#include "ray.h"

class Camera
{
private:
    double m_half_width, m_half_height, m_pixel_size;

public:
    int hsize, vsize;
    double fov;
    Matrix transform;

    Camera(int vsize, int hsize, double fov, Matrix transform = matrix::eye(4));

    double pixel_size() const;
    Ray ray_for_pxiel(int x, int y) const;
};

#endif