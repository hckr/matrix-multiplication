#include <stdio.h>
#include <random>

size_t integer_part_size(std::string str) {
    return str.substr(0, str.find('.')).size();
}

size_t fractional_part_size(std::string str) {
    auto decimal_point_pos = str.find('.');
    if (decimal_point_pos == std::string::npos) {
        return 0;
    }
    return str.substr(decimal_point_pos + 1).size();
}

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        printf("Usage: %s num_rows num_cols min_val max_val\n", argv[0]);
        return 1;
    }

    const int num_rows = std::atoi(argv[1]);
    const int num_cols = std::atoi(argv[2]);

    if (num_rows <= 0 || num_cols <= 0) {
        puts("Error: please provide posivie matrix dimensions.\n");
        return 2;
    }

    const double min_val = std::atof(argv[3]);
    const double max_val = std::atof(argv[4]);

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

    for (int r = 0; r < num_rows; ++r) {
        for (int c = 0; c < num_cols; ++c) {
            printf("%*.*f ", whole_len, frac_len, dis(gen));
        }
        puts("");
    }

    return 0;
}
