#include "pmergesort.h"

using namespace std;

void
swap(int* a, int x, int y) {
	int tmp;
	tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

void
smerge(int* a, int first1, int last1, int first2, int last2) {
	int b, c, d;
	int half1 = last1 - first1 + 1;
	int half2 = last2 - first2 + 1;
	int a1[half1];
	int a2[half2];
	for(int i = 0; i < half1; i++)
		a1[i] = a[first1 + i];
	for(int i = 0; i < half2; i++)
		a2[i] = a[first2 + i];
	b = 0;
	c = 0;
	d = first1;
	while (b < half1 && c < half2) {
		if(a1[b] <= a2[c]) {
			a[d] = a1[b];
			b++;
		} else {
			a[d] = a2[c];
			c++;
		}
		d++;
	}
	while(b < half1) {
		a[d] = a1[b];
		b++;
		d++;
	}
	while(c < half2) {
		a[d] = a2[c];
		c++;
		d++;
	}
}

void
pmerge(int* a, int first, int last, int mid, int my_rank, int p) {
	/* hell goes here */
	cout << endl << "last: " << last << endl;
	int x = ceil(last / LOG(last));
	cout << endl << "x: " << x << endl;
	int *sranka = new int[x];
	int *srankb = new int[x];
	int local_start = my_rank;
	int partition = ceil((last / 2) / LOG(last));

	for (int i = local_start; i < partition; i += p)
		sranka[i] = Rank(a, local_start, last / 2, );

	MPI_Allreduce(a, a, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
}

void
mergesort(int* a, int first, int last, int my_rank, int p) {
	int mid;
  
	if (last <= first)
		return;

	if (first + 1 == last)
		if (a[first] > a[last]) {
			swap(a, first, last);
			return;
		}

	mid = (first + last) / 2;
	//mergesort(a, first, mid, my_rank, p);
	//mergesort(a, mid + 1, last, my_rank, p);
	//smerge(a, first, mid, mid + 1, last);
	pmerge(a, first, last, mid, my_rank, p);
}
