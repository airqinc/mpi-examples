#!/bin/bash
file=$1
num_proc=$2
dir=bin
bin_file=${file/\.c/}

mpicc -std=c99 $file -o $dir/$bin_file && mpiexec -n $2 $dir/$bin_file
# chmod 744 me
