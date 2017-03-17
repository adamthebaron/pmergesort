#include "pmergesort.h"

using namespace std;

int
main(int argc, char **argv) {
  int *a;
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
    cout << "n: ";
    cin >> n;
    /* broadcast n to all processors */
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WOLRD);
    a = genarr(n);
    cout << "unsorted:" << endl;
    cout << "rank: " << my_rank << ": ";
    for(int i = 0; i < n; i++)
      cout << a[i] << " ";
    /* broadcast array to all processors */
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
  }
  else {
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WOLRD);
    a = new int[n];
    /* broadcast array to all processors */
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "rank: " << my_rank << ": ";
    for(int i = 0; i < n; i++)
      cout << a[i] << " ";
  }
    mergesort(a, 0, n - 1);
    cout << "sorted:" << endl;

    for(int i = 0; i < n; i++)
      cout << "a[" << i << "]: " << a[i] << endl;

  MPI_Finalize();
  return 0;
}
