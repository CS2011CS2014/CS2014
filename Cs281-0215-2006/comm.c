/*
Karanja E. Mwangi
Cs281-0215/2006

MPI_Send, MPI_Recv example. Communicates the number "723" from process 0
to process 1.*/


#include <mpi.h> 		//contains the MPI function types declarations
#include <stdio.h>		//standard buffer input/output
#include <stdlib.h>		//standard library definitions

int main(int argc, char** argv) 
{
  // Initialize the MPI system, must be the first statement in an MPI program
  MPI_Init(NULL, NULL);

  //determines the rank of the calling process in the communicator "Comm"
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  //Determines the size of the group assocaited with the communicator "Comm"
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task, if less than "2" abort program
  if (world_size < 2) 
   {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);  //stderr-default error handler
    MPI_Abort(MPI_COMM_WORLD, 1); 
  }

  int number=723;
  if (my_rank == 0)
   {
    // If we are rank 0, set the number to 723 and send it to process 1
    
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
 else if (my_rank == 1) 
   {
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
  }
  MPI_Finalize();
}
