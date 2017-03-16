#include <iostream>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

/* merge.cpp */
void mergesort(int* a, int first, int last);
void smerge(int* a, int first1, int last1, int first2, int last2);
void pmerge(int*a, int first, int last, int mid);
void swap(int* a, int x, int y);

/* rank.cpp */
int rank(int* a, int first, int last, int valToFind);

/* genarr.cpp */
int* genarr(int n);

/* main.cpp */
int main(int argc, char ** argv);
void initenv(int argc, char **argv, int my_rank, int p);
