#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#define LOG(x) log(x) / log(2)

/* merge.cpp */
void mergesort(int* a, int first, int last);
void smerge(int* a, int first1, int last1, int first2, int last2);
void pmerge(int*a, int first, int last, int mid);
void swap(int* a, int x, int y);

/* rank.cpp */
/* gotta use uppercase R
 * because prototype conflicts with std::rank.
 * i could just not use std namespace but, yknow...
 * i could just not use c++ either
 */
int Rank(int* a, int first, int last, int valToFind);

/* genarr.cpp */
int* genarr(int n);

/* main.cpp */
int main(int argc, char ** argv);
