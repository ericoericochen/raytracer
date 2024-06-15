#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include "tuple.h"

class Matrix
{

private:
    int m_dim;
    double *m_matrix;

public:
    Matrix(int dim = 4);
    Matrix(int dim, double *values);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    int dim() const;
    bool operator==(const Matrix &other) const;
    bool operator!=(Matrix &other) const;
    double get(int i, int j) const;
    void set(int i, int j, double val);
    Matrix T() const;
    Matrix operator*(const Matrix &other) const;
    Tuple operator*(const Tuple &other) const;
    double determinant() const;
    bool is_invertible() const;
    Matrix submatrix(int row, int col) const;
    double minor(int i, int j) const;
    double cofactor(int i, int j) const;
    Matrix inverse() const;
    std::string to_string() const;
};

Matrix Matrix4x4(double vals[16]);
Matrix Matrix4x4();

Matrix Matrix3x3(double vals[9]);
Matrix Matrix3x3();

Matrix Matrix2x2(double vals[4]);
Matrix Matrix2x2();

namespace matrix
{
    Matrix eye(int dim);
    Matrix translation(double x, double y, double z);
    Matrix scaling(double x, double y, double z);
    Matrix rotation_x(double radians);
    Matrix rotation_y(double radians);
    Matrix rotation_z(double radians);
    Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy);
    Matrix view_transform(Tuple &from, Tuple &to, Tuple &up);
}

#endif