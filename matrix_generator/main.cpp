#include <stdio.h>
#include <random>
#include <sstream>

std::size_t integer_part_size(std::string str) {
    return str.substr(0, str.find('.')).size();
}

std::size_t fractional_part_size(std::string str) {
    auto decimal_point_pos = str.find('.');
    if (decimal_point_pos == std::string::npos) {
        return 0;
    }
    return str.substr(decimal_point_pos + 1).size();
}

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        printf("Usage: %s num_rows num_cols min_val max_val\n", argv[0]);
        puts("\nIn the first line of output there are two numbers separated by a space: "
             "number of rows and columns of the generated matrix. Next lines are consecutive "
             "rows of the matrix consisting of random numbers between min_val and max_val "
             "separated by spaces. Length of the fractional part is determined based on "
             "the input values of min_val and max_val.\n\nExamples:\n");
        printf("%s 3 3 -1 1\n", argv[0]);
        puts("Could output for example:\n"
             "3 3\n"
             " 0  0  1 \n"
             "-1 -1 -1 \n"
             " 0 -1 -0 \n");
        printf("%s 3 4 -1.00 1.00\n", argv[0]);
        puts("Could output for example:\n"
             "3 4\n"
             "-0.45 -0.73 -0.74 -0.32 \n"
             " 0.10 -0.73  0.58 -0.10 \n"
             "-0.23  0.30 -0.22  0.09 ");
        return 1;
    }

    unsigned num_rows;
    std::istringstream(argv[1]) >> num_rows;
    unsigned num_cols;
    std::istringstream(argv[2]) >> num_cols;

    if (num_rows <= 0 || num_cols <= 0) {
        puts("Error: please provide posivie matrix dimensions.\n");
        return 2;
    }

    double min_val;
    std::istringstream(argv[3]) >> min_val;
    double max_val;
    std::istringstream(argv[4]) >> max_val;

    const int int_len = std::max(integer_part_size(argv[3]), integer_part_size(argv[4]));
    const int frac_len = std::max(fractional_part_size(argv[3]), fractional_part_size(argv[4]));
    int whole_len = int_len + frac_len;
    if (frac_len > 0) {
        whole_len += 1; // dot
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_val, max_val);

    printf("%d %d\n", num_rows, num_cols);

    for (unsigned r = 0; r < num_rows; ++r) {
        for (unsigned c = 0; c < num_cols; ++c) {
            printf("%*.*f ", whole_len, frac_len, dis(gen));
        }
        puts("");
    }

    return 0;
}
