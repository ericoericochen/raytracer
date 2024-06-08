#include <cassert>
#include <iostream>
#include <vector>
#include "../src/matrix.cpp"

using namespace std;

int main()
{
    vector<vector<double>> val;

    val = {
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}};

    // test initialization
    Matrix m = Matrix(4, val);

    cout << m.to_string() << endl;

    assert(m.get(0, 0) == 1);
    assert(m.get(0, 3) == 4);
    assert(m.get(1, 0) == 5.5);
    assert(m.get(1, 2) == 7.5);
    assert(m.get(2, 2) == 11);
    assert(m.get(3, 0) == 13.5);
    assert(m.get(3, 2) == 15.5);

    // 2x2 matrix
    val = {
        {-3, 5},
        {1, -2}};
    m = Matrix(2, val);

    cout << m.to_string() << endl;

    assert(m.get(0, 0) == -3);
    assert(m.get(0, 1) == 5);
    assert(m.get(1, 0) == 1);
    assert(m.get(1, 1) == -2);

    // 3x3 matrix
    val = {
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}};
    m = Matrix(3, val);

    cout << m.to_string() << endl;

    assert(m.get(0, 0) == -3);
    assert(m.get(1, 1) == -2);
    assert(m.get(2, 2) == 1);

    // equality
    Matrix A, B;
    vector<vector<double>> a_val, b_val;

    a_val = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};

    b_val = a_val;
    A = Matrix(4, a_val);
    B = Matrix(4, b_val);

    assert(A == B);

    b_val = {
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}};

    B = Matrix(4, b_val);

    assert(A != B);

    // matrix multiplication

    //     Scenario: Multiplying two matrices
    // Given the following matrix A:
    // | 1 | 2 | 3 | 4 |
    // | 5 | 6 | 7 | 8 |
    // | 9 | 8 | 7 | 6 |
    // | 5 | 4 | 3 | 2 |
    // And the following matrix B:
    // | -2 | 1 | 2 | 3 |
    // | 3 | 2 | 1 | -1 |
    // | 4 | 3 | 6 | 5 |
    // | 1 | 2 | 7 | 8 |
    // Then A * B is the following 4x4 matrix:
    // | 20| 22 | 50 | 48 |
    // | 44| 54 | 114 | 108 |
    // | 40| 58 | 110 | 102 |
    // | 16| 26 | 46 | 42 |

    a_val = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};
    b_val = {
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}};

    A = Matrix(4, a_val);
    B = Matrix(4, b_val);

    vector<vector<double>> c_val = {{20, 22, 50, 48},
                                    {44, 54, 114, 108},
                                    {40, 58, 110, 102},
                                    {16, 26, 46, 42}};
    Matrix answer = Matrix(4, c_val);

    Matrix C = A.matmul(B);

    cout << C.to_string() << endl;

    assert(C == answer);

    return 0;
}