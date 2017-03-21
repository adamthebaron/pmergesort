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
sort(int *a, int n) {
	int b, c, j;
	for (int i = 1; i < n; i++) {
		c = a[i];
		for (j = i - 1; j >= 0 && a[j] > c; j--)
			a[j + 1] = a[j];
		a[j + 1] = c;
	}
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
	int partition = ceil((last / 2) / log2(last / 2));
	int *sranka = new int[partition];
	int *srankb = new int[partition];
	int *localsranka = new int[partition];
	int *localsrankb = new int[partition];
	int *win = new int[last + 1];
	int local_start = my_rank;
	int index = 0;
	int *localpointsa = new int[2 * partition];
	int *localpointsb = new int[2 * partition];
	int *pointsa = new int[2 * partition];
	int *pointsb = new int[2 * partition];
	cout << "last: " << last << endl;
	cout << "partition: " << partition << endl;
	for (int i = 0; i < partition; i++) {
		sranka[i] = 0;
		srankb[i] = 0;
		localsranka[i] = 0;
		localsrankb[i] = 0;
	}

	for (int i = 0; i < 2 * partition; i++) {
		pointsa[i] = 0;
		pointsb[i] = 0;
		localpointsa[i] = 0;
		localpointsb[i] = 0;
	}

	for (int i = 0; i < last; i++)
		win[i] = 0;

	cout << endl;
	for (int i = local_start; i < partition; i += p) {
		index = i * log2(mid);
		cout << "index: " << index << " i: " << i;
		localsranka[i] = Rank(a, mid + 1, last, a[index]);
		localsrankb[i] = Rank(a, 0, mid, a[index + mid + 1]);
		cout << " a[index]: " << a[index] << " a[index + mid + 1]: " << a[index + mid + 1] << " index: " << index << " index + mid + 1: " << index + mid + 1 << endl;
	}

	MPI_Allreduce(localsranka, sranka, partition, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(localsrankb, srankb, partition, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	cout << "sranka: ";

	for (int i = 0; i < partition; i++)
		cout << sranka[i] << " ";

	cout << "srankb: ";

	for (int i = 0; i < partition; i++)
		cout << srankb[i] << " ";
	cout << endl;

	for (int i = my_rank; i < partition; i += p) {
		localpointsa[i] = i * log2(mid);
		localpointsb[i] = i * log2(mid);
	}

	for (int i = my_rank; i < partition; i += p) {
		localpointsa[partition + i] = sranka[i];
		localpointsb[partition + i] = srankb[i];
	}

	pointsa[2 * partition] = 0;
	pointsb[2 * partition] = 0;

	MPI_Allreduce(localpointsa, pointsa, 2 * partition, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(localpointsb, pointsb, 2 * partition, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	sort(pointsa, 2 * partition);
	sort(pointsb, 2 * partition);

	/*
	if (my_rank == 0) {
	cout << "pointsa: ";
	for (int i = 0; i < partition * 2; i++)
		cout << pointsa[i] << " ";
	cout << endl;

	cout << "pointsb: ";
	for (int i = 0; i < partition * 2; i++)
		cout << pointsb[i] << " ";
	cout << endl;
	}
	*/

	for (int i = my_rank; i < 2 * partition - 1; i += p)
		smerge(a, pointsa[i], pointsa[i + 1], pointsb[i], pointsb[i + 1]);

	delete [] sranka;
	delete [] srankb;
	delete [] pointsa;
	delete [] pointsb;
	delete [] localsranka;
	delete [] localsrankb;
	delete [] localpointsa;
	delete [] localpointsb;
	delete [] win;
}

void
mergesort(int* a, int first, int last, int my_rank, int p) {
	int mid = ceil((first + last) / 2);

	cout << "first: " << first << " ";
	cout << "mid: " << mid << " ";
	cout << "last: " << last << endl;

	//if (last <= 100)
	//	pmerge(a, first, last, mid, my_rank, p);

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
