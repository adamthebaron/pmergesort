#include "pmergesort.h"

using namespace std;

int
Rank(int* a, int first, int last, int valToFind) {
	int m = ceil(last / 2);

	if (last < 1)
		return 0;

	if (last == 1) {
		if (valToFind < a[1])
			return 0;
		else
			return 1;
	}

	if (valToFind < a[m])
		return Rank(a, first, m - 1, valToFind);
	else
		return m + Rank(&a[m], m + 1, last, valToFind);
}
