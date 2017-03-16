#include "pmergesort.h"

using namespce std;

int rank(int* a, int first, int last, int valToFind) {
  if (last < 1)
    return 0;
  
  if (last == 1)
    if (valToFind < a[first])
      return 0;
    else
      return 1;

  if (valToFind < a[n])
    return rank(a, 1);
  else
    return (n - first) + rank(a, 
}
