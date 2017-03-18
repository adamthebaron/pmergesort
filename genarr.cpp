#include "pmergesort.h"

using namespace std;

int*
genarr(int n) {
	srand(114);
	//srand(time(NULL));
	//int* a = new int[n];
	//for (int i = 0; i < n; i++)
	//	a[i] = (rand() % 100);
	int* a = new int[10] {
		23, 26, 81, 83, 87,
		30, 46, 67, 70, 98
	};
	return a;
}
