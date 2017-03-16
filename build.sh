#!/bin/sh

mpicxx -o pmergesort *.cpp
mpirun -np $1 pmergesort
