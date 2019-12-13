#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

for p_num in 1 2; do
    for size in 100 500 1000 2000; do
        $DIR/execute_different_thread_nums.sh $(realpath --relative-to="${PWD}" "$DIR/../dist")/matrix_multiplication_parallel$p_num $size.in $size.in ${size}p__NUM__.out
    done
done
