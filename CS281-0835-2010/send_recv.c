
/*
NAME: DENNIS MWANGI BARU
REG.NO:CS281-0835/2010
UNIT: PARALLEL SYSTEMS
UNIT CODE: ICS 2410
ASSIGNMENT:
MPI_Send, MPI_Recv example. Communicates the number "1963" from process 0
to processe 1.
*/


#include <mpi.h> 		//coantains the MPI function types declarations
#include <stdio.h>		//standard buffer input/output
#include <stdlib.h>		//standard library definitions

int main(int argc, char** argv) 
{
  // Initialize the MPI system.
  MPI_Init(NULL, NULL);

  
  int rank;
  int world_size;
  //determines the rank of the calling process in the communicator "Comm"
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //Determines the size of the group assocaited with the communicator "Comm"
  
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // At least 2 processes for this task, if less than "2" abort program
  if (world_size < 2) 
   {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);  
    MPI_Abort(MPI_COMM_WORLD, 1); 
  }

  int number=1963;
  if (rank == 0)
   {
    // If we are rank 0, set the number to 1963 and send it to process 1
    
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
 else if (rank == 1) 
   {
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
  }
  
  MPI_Finalize();
  return 0;
}
