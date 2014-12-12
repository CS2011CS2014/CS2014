/* 
	This program prints a Hello world message from every node
	Each process prints its rank number 
	Each process also prints the total number of processers.
*/

#include <mpi.h>
#include <stdio.h>
 
int main (int argc, char* argv[])
{
  int rank, size;
 
  MPI_Init (&argc, &argv);      /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
  printf( "Hello world from process %d of %d\n", rank, size );
  MPI_Finalize();
  return 0;
}
