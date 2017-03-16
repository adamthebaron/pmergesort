#include <iostream>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

void mergesort(int* a, int first, int last);
void smerge(int* a, int first1, int last1, int first2, int last2);
int rank(int* a, int first, int last, int valToFind);
void pmerge(int*a, int first, int last, int mid);
int* genarr(int n);
void initenv(int argc, char **argv, int my_rank, int p);
