#include "pmergesort.h"

using namespce std;

int rank(int* a, int first, int last, int valToFind) {
  int m = last / 2;
  if (last < 1)
    return 0;
  
  if (last == 1)
    if (valToFind < a[first])
      return 0;
    else
      return 1;

  if (valToFind < a[m])
    return rank(a, 1, m - 1, valToFind);
  else
    return m - first + rank(a, m + 1, last, valToFind);
}
