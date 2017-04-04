#!/bin/bash
file_path=$1
num_proc=$2
filename=$(basename $1)
dir=bin
bin_file=${filename/\.c/}

mpicc -std=gnu99 -lm $file_path -o $dir/$bin_file && mpiexec -n $num_proc $dir/$bin_file
# chmod +x me
