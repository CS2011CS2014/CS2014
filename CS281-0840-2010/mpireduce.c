#include <stdio.h>
#include "mpi.h"

int main (int argc, char *argv[])
{
  int rank, size, recvbuf;
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  
  printf ("Processor %d submitting my rank for summation \n",rank);
  
  MPI_Reduce (&rank,&recvbuf,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
  
  if (rank == 0)
  {
    printf ("Processor %d  Total of ranks is: %d \n",rank, recvbuf);
  }
  
  MPI_Finalize ();

}
