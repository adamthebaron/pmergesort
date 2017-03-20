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
	/* parahell */
	//int x = ceil((last / 2) / LOG(last / 2));
	int x = ceil(last / LOG(last));
	int m = ceil(last / 2);
	int *sranka = new int[x];
	int *srankb = new int[x];
	int *localsranka = new int[x];
	int *localsrankb = new int[x];
	int local_start = my_rank;
	//int partition = ceil((last / 2) / ((last / 2) / LOG(last / 2)));
	int partition = ceil((last / 2) / LOG(last / 2));
	int index;

	for (int i = 0; i < x; i++) {
		sranka[i] = 0;
		srankb[i] = 0;
		localsranka[i] = 0;
		localsrankb[i] = 0;
	}

	for (int i = local_start; i < partition; i += p) {
		index = i + LOG(m);
		cout << "index: " << index << " i: " << i;
		//localsranka[i] = Rank(a, local_start, m, a[index]);
		//localsrankb[i] = Rank(a, local_start + m, last, a[index]);
		localsranka[i] = Rank(a, m, last, a[index]);
		localsrankb[i] = Rank(a, 0, m - 1, a[index + m]);
		cout << " a[index]: " << a[index] << " a[index + m]: " << a[index + m] << endl;
	}

	cout << "my_rank: " << my_rank << endl;
	cout << "localsranka: ";

	for(int i = 0; i < x; i++) {
		if (!localsranka[i])
			continue;
		cout << "(i = " << i << ") " << localsranka[i] << " ";
	}

	cout << endl;
	cout << "localsrankb: ";

	for(int i = 0; i < x; i++) {
		if (!localsrankb[i])
			continue;
		cout << "(i = " << i << ") " << localsrankb[i] << " ";
	}

	cout << endl;

	MPI_Allreduce(&localsranka, &sranka, m, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&localsrankb, &srankb, m, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	cout << "sranka: ";

	for (int i = 0; i < x; i++)
		cout << sranka[i] << " ";

	cout << "srankb: ";

	for (int i = 0; i < x; i++)
		cout << srankb[i] << " ";
}

void
mergesort(int* a, int first, int last, int my_rank, int p) {
	int mid = (first + last) / 2;

	if (last <= 100)
		pmerge(a, first, last, mid, my_rank, p);

	if (last <= first)
		return;

	if (first + 1 == last)
		if (a[first] > a[last]) {
			swap(a, first, last);
			return;
		}

	mergesort(a, first, mid, my_rank, p);
	mergesort(a, mid + 1, last, my_rank, p);
	//smerge(a, first, mid, mid + 1, last);
	pmerge(a, first, last, mid, my_rank, p);
}
