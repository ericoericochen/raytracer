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

    return 0;
}