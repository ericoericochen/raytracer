#include <cmath>
#include <iostream>
#include "../include/camera.h"
#include "../include/tuple.h"

Camera::Camera(int hsize, int vsize, double fov, Matrix transform) : hsize(hsize), vsize(vsize), fov(fov), transform(transform)
{
    double half_view = tan(fov / 2);
    double aspect = (double)hsize / (double)vsize;

    if (aspect >= 1)
    {
        this->m_half_width = half_view;
        this->m_half_height = half_view / aspect;
    }
    else
    {
        this->m_half_width = half_view * aspect;
        this->m_half_height = half_view;
    }

    this->m_pixel_size = (this->m_half_width * 2) / this->hsize;
}

// canvas is 1 unit away from camera
double Camera::pixel_size() const
{
    return this->m_pixel_size;
}

Ray Camera::ray_for_pxiel(int x, int y) const
{
    // the offset from the edge of the canvas to the pixel's center
    double xoffset = (x + 0.5) * this->pixel_size();
    double yoffset = (y + 0.5) * this->pixel_size();

    // the untransformed coordinates of the pixel in world space.
    // (remember that the camera looks toward -z, so +x is to the *left*.)
    double world_x = this->m_half_width - xoffset;
    double world_y = this->m_half_height - yoffset;

    // using the camera matrix, transform the canvas point and the origin,
    // and then compute the ray's direction vector.
    // (remember that the canvas is at z=-1)
    Tuple pixel = this->transform.inverse() * tuple::point(world_x, world_y, -1);
    Tuple origin = this->transform.inverse() * tuple::point(0, 0, 0);
    Tuple direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}