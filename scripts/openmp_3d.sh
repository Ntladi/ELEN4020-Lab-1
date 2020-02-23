#!/bin/bash
 
# This displays the real world time taken to execute the 3D
# OpenMP parallelization implementation using a variety of threads
# and dimentions

# 10 x 10 matrix

echo ""

echo "Computing a 10x10x10 matrix using OpenMP with 1 thread:"
{ time ../executables/openmp_3d 1 10 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 10x10x10 matrix using OpenMP with 2 threads:"
{ time ../executables/openmp_3d 2 10 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 10x10x10 matrix using OpenMP with 4 threads:"
{ time ../executables/openmp_3d 4 10 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 10x10x10 matrix using OpenMP with 8 threads:"
{ time ../executables/openmp_3d 8 10 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 10x10x10 matrix using OpenMP with 64 threads:"
{ time ../executables/openmp_3d 64 10 ls -l >/dev/null; } 2>&1 | grep real

# 20 x 20 matrix

echo ""

echo "Computing a 20x20x20 matrix using OpenMP with 1 thread:"
{ time ../executables/openmp_3d 1 20 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 20x20x20 matrix using OpenMP with 2 threads:"
{ time ../executables/openmp_3d 2 20 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 20x20x20 matrix using OpenMP with 4 threads:"
{ time ../executables/openmp_3d 4 20 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 20x20x20 matrix using OpenMP with 8 threads:"
{ time ../executables/openmp_3d 8 20 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 20x20x20 matrix using OpenMP with 64 threads:"
{ time ../executables/openmp_3d 64 20 ls -l >/dev/null; } 2>&1 | grep real

# 30 x 30 threads

echo ""

echo "Computing a 30x30x30 matrix using OpenMP with 1 thread:"
{ time ../executables/openmp_3d 1 30 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 30x30x30 matrix using OpenMP with 2 threads:"
{ time ../executables/openmp_3d 2 30 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 30x30x30 matrix using OpenMP with 4 threads:"
{ time ../executables/openmp_3d 4 30 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 30x30x30 matrix using OpenMP with 8 threads:"
{ time ../executables/openmp_3d 8 30 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 30x30x30 matrix using OpenMP with 64 threads:"
{ time ../executables/openmp_3d 64 30 ls -l >/dev/null; } 2>&1 | grep real

# 100 x 100 matrix

echo ""

echo "Computing a 100x100x100 matrix using OpenMP with 1 thread:"
{ time ../executables/openmp_3d 1 100 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 100x100x100 matrix using OpenMP with 2 threads:"
{ time ../executables/openmp_3d 2 100 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 100x100x100 matrix using OpenMP with 4 thread:"
{ time ../executables/openmp_3d 4 100 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 100x100x100 matrix using OpenMP with 8 threads:"
{ time ../executables/openmp_3d 8 100 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 100x100x100 matrix using OpenMP with 64 threads:"
{ time ../executables/openmp_3d 64 100 ls -l >/dev/null; } 2>&1 | grep real

# 250 x 250 matrix

echo ""

echo "Computing a 250x250x250 matrix using OpenMP with 1 thread:"
{ time ../executables/openmp_3d 1 250 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 250x250x250 matrix using OpenMP with 2 thread:"
{ time ../executables/openmp_3d 2 250 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 250x250x250 matrix using OpenMP with 4 threads:"
{ time ../executables/openmp_3d 4 250 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 250x250x250 matrix using OpenMP with 8 threads:"
{ time ../executables/openmp_3d 8 250 ls -l >/dev/null; } 2>&1 | grep real

echo "Computing a 250x250x250 matrix using OpenMP with 64 threads:"
{ time ../executables/openmp_3d 64 250 ls -l >/dev/null; } 2>&1 | grep real
