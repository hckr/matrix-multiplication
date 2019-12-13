#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MATRIX_GENERATOR=./$(realpath --relative-to="${PWD}" "${DIR}/../dist/matrix_generator")

for size in 100 500 1000 2000; do
    command="$MATRIX_GENERATOR $size $size -1.00 1.00 > $size.in"
    echo $command
    eval $command
done
