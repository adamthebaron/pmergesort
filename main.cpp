#include "pmergesort.h"

using namespace std;

int
main(int argc, char **argv) {
	int* a;
	int my_rank;
	int p;
	int source;
	int dest;
	int tag = 0;
	char message[100];
	MPI_Status status;
	int n = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if (my_rank == 0) {
		//cout << "n: ";
		//cin >> n;
		//a = genarr(n);
		n = 64;
		a = new int[n]{
	  /* 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 */
		12, 14, 19, 20, 25, 32, 36, 39, 40, 41, 43, 44, 48, 49, 51, 55, 56, 57, 58, 65, 67, 69, 70, 72, 74, 77, 79, 80, 81, 84, 88, 98,
		 3,  4,  5,  8,  9, 10, 13, 15, 17, 21, 24, 26, 29, 33, 34, 37, 42, 45, 47, 53, 59, 61, 66, 68, 71, 75, 78, 82, 83, 87, 91, 93
		};
		/* broadcast n to all processors */
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		cout << "unsorted:" << endl;

		for (int i = 0; i < n; i++)
			cout << a[i] << " ";

		cout << endl;
		/* broadcast array to all processors */
		MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		a = new int[n];
		/* broadcast array to all processors */
		MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
	}

	mergesort(a, n, my_rank, p);
	MPI_Finalize();
	return 0;
}
