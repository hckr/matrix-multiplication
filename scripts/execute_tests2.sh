#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

for size in 1000 2000; do
    for schedule in static dynamic guided; do
        for chunk in 10 50 100; do
            $DIR/execute_different_thread_nums.sh OMP_SCHEDULE=${schedule},${chunk} $(realpath --relative-to="${PWD}" "$DIR/../dist")/matrix_multiplication_parallel1 $size.in $size.in ${size}p__NUM__${schedule}${chunk}.out
        done
    done
done
