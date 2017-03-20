#include "pmergesort.h"

using namespace std;

/*int
Rank(int* a, int first, int last, int valToFind) {
	int m = ceil(((last - first) / 2) + first);

	if (last < 1)
		return 0;

	if (last == 1) {
		if (valToFind < a[1])
			return 0;
		else
			return 1;
	}
	
	if (first == last) {
		if (valToFind < a[first])
			return first;
		else
			return first + 1;
	}

	if (valToFind < a[m])
		return Rank(a, first, m - 1, valToFind);
	else
		return Rank(&a[m], m + 1, last, valToFind);
}
*/

int
Rank(int *a, int first, int last, int valToFind) {
	if(last-first == 0) {
		if(valToFind<a[first])
			return 0; 
		else
			return 1;
	}
	
	if(last < first)
		return 0;
	
	int m = ((last - first) / 2) + first; 
 
	if(valToFind < a[m])
		return Rank(a, first, m - 1, valToFind);
	else 
		return (m - first + 1) + Rank(a, m + 1, last, valToFind);
}
