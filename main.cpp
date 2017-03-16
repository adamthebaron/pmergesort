#include "pmergesort.h"

using namespace std;

/*
 * mpicxx -o pmergesort main.cpp rank.cpp merge.cpp genarr.cpp
 * mpirun -np 4 pmergesort
 */

void initenv(int argc, char **argv, int my_rank, int p) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
}

int main(int argc, char **argv) {
  int *a;
  int my_rank;
  int p;
  int source;
  int dest;
  int tag = 0;
  char message[100];
  MPI_Status status;
  int n = 0;

  if (my_rank == 0) {
    cout << "n: ";
    cin >> n;
    a = genarr(n);
  }
  
  for(int i = 0; i < n; i++)
    cout << "a[" << i << "]: " << a[i] << endl;
  
  initenv(argc, argv, my_rank, p);
  /* broadcast array to all processors */
  MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);
  mergesort(a, 0, n - 1);
  cout << "sorted array: " << endl;

  for(int i = 0; i < n; i++)
    cout << "a[" << i << "]: " << a[i] << endl;

  MPI_Finalize();
  return 0;
}
