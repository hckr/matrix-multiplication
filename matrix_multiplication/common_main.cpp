#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "Matrix.hpp"

extern void multiply(const Matrix &m1, const Matrix &m2, Matrix &result);

Matrix loadMatrix(std::string file_name) {
    if (file_name == "-") {
        return Matrix(std::cin);
    }
    std::ifstream stream(file_name);
    return Matrix(stream);
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        printf("Usage: %s matrix1_file matrix2_file result_file\n", argv[0]);
        puts("In order to load from stdin instead of a file, replace file name with -");
        return 1;
    }

    std::unique_ptr<Matrix> first;
    std::unique_ptr<Matrix> second;

#pragma omp parallel sections
    {
#pragma omp section
        {
            first.reset(new Matrix(loadMatrix(argv[1])));
        }
#pragma omp section
        {
            second.reset(new Matrix(loadMatrix(argv[2])));
        }
    }

    Matrix result(first->numRows(), second->numCols());

    clock_t start = clock();

    multiply(*first, *second, result);

    std::cerr << "Multiplication took " << ((float)start) / CLOCKS_PER_SEC << " s.\n";

    if (std::string(argv[3]) == "-") {
        result.stream(std::cout);
    } else {
        std::ofstream stream(argv[3]);
        result.stream(stream);
    }

    return 0;
}
