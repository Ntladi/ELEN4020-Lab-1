#!/bin/bash

cd ../executables
make
echo "Compiling all files"
cd ../scripts
./openmp_2d.sh
./openmp_3d.sh
./pthreads_2d.sh
./pthreads_3d.sh


