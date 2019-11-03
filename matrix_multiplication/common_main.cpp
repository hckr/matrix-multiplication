#include <iostream>
#include <fstream>
#include <string>

#include "Matrix.hpp"

extern void multiply(const Matrix &m1, const Matrix &m2, Matrix &result);

Matrix loadMatrix(std::string file_name) {
    if (file_name == "-") {
        return Matrix(std::cin);
    }
    std::ifstream stream(file_name);
    return Matrix(stream);
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Usage: %s matrix1_file matrix2_file\n", argv[0]);
        puts("In order to load from stdin instead of a file, replace file name with -");
        return 1;
    }

    Matrix first = loadMatrix(argv[1]);
    Matrix second = loadMatrix(argv[2]);
    Matrix result(first.numRows(), second.numCols());

    multiply(first, second, result);

    result.stream(std::cout);

    return 0;
}
