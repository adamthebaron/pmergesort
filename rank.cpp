#include "pmergesort.h"

using namespace std;

int
Rank(int *a, int last, int valToFind) {
	if (last == 1)
		if (valToFind < a[0])
			return 0;
		else
			return 1;
	else
		if (valToFind < a[last / 2])
			return Rank(a, last / 2, valToFind);
		else
			return (last / 2) + Rank(&a[last / 2], last / 2, valToFind);
}
