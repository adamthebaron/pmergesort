#include "pmergesort.h"

using namespace std;

void
Swap(int* a, int x, int y) {
	int tmp;
	tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

void
smerge(int* a, int a0, int a1, int* b, int b0, int b1, int* c, int c0, int c1) {
	int j = a0;
	int k = b0;
	int l = c0;

	while (j <= a1 && k <= b1)
		if (a[j] < b[k])
			c[k++] = a[j++];
		else
			c[k++] = b[k++];

	while (j <= a1)
		c[k++] = a[j++];
	while (k <= b1)
		c[k++] = b[k++];
}

void
pmerge(int* a, int first, int last, int mid, int my_rank, int p) {
	/* parahell */
	int partition = ceil((double) (last / 2) / log2(last / 2));
	int *sranka = new int[partition];
	int *srankb = new int[partition];
	int *localsranka = new int[partition];
	int *localsrankb = new int[partition];
	int *win = new int[last];
	int *localwin = new int[last];
	int local_start = my_rank;
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
	}

	for (int i = 0; i < last; i++) {
		win[i] = 0;
		localwin[i] = 0;
	}

	for (int i = local_start; i < partition; i += p) {
		int arr_index = i * log2(mid);
		localsranka[i] = Rank(a, mid + 1, last, a[arr_index]);
		localsrankb[i] = Rank(a, 0, mid, a[arr_index + mid + 1]);
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

	for (int i = my_rank; i < partition; i++) {
		pointsa[i] = i * log2(mid);
		pointsb[i] = i * log2(mid);
	}

	for (int i = my_rank; i < partition; i++) {
		pointsa[partition + i] = srankb[i];
		pointsb[partition + i] = sranka[i];
	}

	sort(pointsa, pointsa + 2 * partition);
	sort(pointsb, pointsb + 2 * partition);

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

	for (int i = my_rank; i < 2 * partition - 1; i += p)
		smerge(a, pointsa[i], pointsa[i + 1] - 1, &a[last / 2], pointsb[i],
			   pointsb[i + 1] - 1, localwin, pointsa[i] + pointsb[i],
           	   pointsb[i + 1] + pointsb[i + 1]);
	smerge(a, pointsa[2 * partition - 1], last / 2 - 1, &a[last / 2],
		   pointsb[2 * partition - 1], last / 2 - 1, localwin,
		   pointsa[2 * partition - 1] + pointsb[2 * partition - 1], last);

	MPI_Allreduce(localwin, win, last + 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	cout << "win: ";
	for (int i = 0; i < last + 1; i++)
		cout << win[i] << " ";
	cout << endl;
	delete [] sranka;
	delete [] srankb;
	delete [] pointsa;
	delete [] pointsb;
	delete [] localsranka;
	delete [] localsrankb;
	delete [] win;
}

void
mergesort(int* a, int first, int last, int my_rank, int p) {
	int mid = ceil((first + last) / 2);

	cout << "first: " << first << " ";
	cout << "mid: " << mid << " ";
	cout << "last: " << last << endl;

	if (last <= 100)
		pmerge(a, first, last, mid, my_rank, p);

	if (last <= first)
		return;

	if (first + 1 == last)
		if (a[first] > a[last]) {
			Swap(a, first, last);
			return;
		}
	mergesort(a, first, mid, my_rank, p);
	mergesort(a, mid + 1, last, my_rank, p);
	//smerge(a, first, mid, mid + 1, last);
	pmerge(a, first, last, mid, my_rank, p);
}
