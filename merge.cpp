#include "pmergesort.h"

using namespace std;

void swap(int* a, int x, int y) {
  int tmp;
  tmp = a[x];
  a[x] = a[y];
  a[y] = tmp;
}

void smerge(int* a, int first1, int last1, int first2, int last2) {
  int b, c, d, e;
  int a1[last1];
  int a2[last2];
  
  for (int i = 0; i < last1; i++)
    a1[i] = a[first1 + i];

  for (int i = 0; i < last2; i++)
    a2[i] = a[first2 + i];

  b = 0;
  c = 0;
  d = first1;
  e = first2;

  while(b < last1 && c < last2) {
    if(a1[b] <= a2[c]) {
      a[d] = a1[b];
      b++;
    } else {
      a[d] = a2[c];
      c++;
    }
    d++;
  }
  
  while(b < last1) {
    a[d] = a1[b];
    b++;
    d++;
  }
  
  while(c < last2) {
    a[d] = a2[c];
    c++;
    d++;
  }
}

void mergesort(int* a, int first, int last) {
  int mid;
  
  if (last <= first)
    return;
  if (first + 1 == last) {
    if (a[first] > a[last])
      swap(a, first, last);
    return;
  }

  mid = (first + last) / 2;
  mergesort(a, first, mid);
  mergesort(a, mid + 1, last);
  pmerge(a, first, last, mid);
}
