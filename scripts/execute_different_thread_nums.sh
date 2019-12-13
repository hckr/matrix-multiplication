#!/bin/bash

orig_command="$@"

for num in 2 4 8 16; do
    command="OMP_NUM_THREADS=$num ${orig_command//"__NUM__"/$num}"
    echo $command
    eval $command
done
