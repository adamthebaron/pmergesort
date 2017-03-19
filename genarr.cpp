#include "pmergesort.h"

using namespace std;

int*
genarr(int n) {
	srand(114);
	//srand(time(NULL));
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = (rand() % 100);
	return a;
}
