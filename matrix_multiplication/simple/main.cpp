#include <iostream>
#include "../Matrix.hpp"

Matrix multiply(const Matrix &m1, const Matrix &m2) {
    if (m1.numCols() != m2.numRows()) {
        throw std::runtime_error("Matrices can't be multiplied: dimensions don't match.");
    }

    Matrix result(m1.numRows(), m2.numCols());

    auto m1a = m1.getArray();
    auto m2a = m2.getArray();
    auto ra = result.getArray();

    for (unsigned r = 0; r < result.numRows(); ++r) {
        for (unsigned c = 0; c < result.numCols(); ++c) {
            double sum = 0;
            for (unsigned i = 0; i < m1.numRows(); ++i) {
                sum = sum + m1a[r * m1.numCols() + i] * m2a[i * m2.numCols() + c];
            }
            ra[r * result.numCols() + c] = sum;
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    Matrix matrix1(std::cin);
    Matrix matrix2(std::cin);

    multiply(matrix1, matrix2).stream(std::cout);

    return 0;
}
