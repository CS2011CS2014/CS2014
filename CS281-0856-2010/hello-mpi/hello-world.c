/**
 * Reg No: CS281-0856/2010
 * Name: BETHUEL MUCHINA
 * 
 * Hello world example using MPI
 */

#include <mpi.h>
#include <stdio.h>
 
int main (int argc, char* argv[])
{
  int rank, size;
 
  MPI_Init (&argc, &argv);      /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
  
  printf( "Howdy from process %d of %d\n", rank, size );
  
  MPI_Finalize();
  return 0;
}
